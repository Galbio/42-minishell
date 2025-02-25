/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:21:54 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/24 23:23:22 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_special_char(char c, char *backslash, char *cur_quote)
{
	if ((c == '\'') && (*cur_quote == '\''))
		return (*cur_quote = 0, 0);
	else if ((*cur_quote == 0) && (c == '\'') && (*backslash == 0))
		return (*cur_quote = '\'', 0);
	else if (*cur_quote == '\'')
		return (1);
	else if ((c == '"') && (*cur_quote == '"') && (*backslash))
		return (*backslash = 0, 1);
	else if ((c == '"') && (*cur_quote == '"'))
		return (*cur_quote = 0, 0);
	else if ((*cur_quote == 0) && (c == '"'))
		return (*cur_quote = '"', 0);
	else if (c == '"')
		return (*cur_quote = '"', 0);
	if ((c == '\\') && (*backslash))
		return (*backslash = 0, 1);
	else if (c == '\\')
		return (*backslash = 1, 0);
	else if (c != '$')
		*backslash = 0;
	return (1);
}

char	*get_var_str(char *str)
{
	int		i;
	char	pare;

	i = -1;
	pare = (str[0] == '(');
	while (str[++i])
	{
		if ((str[i] != '_') && (!ft_isalnum(str[i])) && (!pare))
			return (ft_substr(str, 0, i));
		else if (str[i] == ')')
			return (ft_substr(str, 0, i + 1));
	}
	return (ft_substr(str, 0, i + 1));
}

int	get_parsed_len(char *str, t_list *envp, t_main_envp *imp)
{
	t_int_tab	infos;

	infos.i = -1;
	infos.res = 0;
	infos.cur_quote = 0;
	infos.backslash = 0;
	while (str[++infos.i])
	{
		if (!check_special_char(str[infos.i], &infos.backslash,
				&infos.cur_quote))
			continue ;
		if ((infos.cur_quote != '\'') && str[infos.i] == '$')
		{
			infos.ptr1 = get_var_str(str + infos.i + 1);
			infos.ptr2 = parse_var(infos.ptr1, envp, imp);
			infos.res += ft_securelen(infos.ptr2);
			infos.i += ft_securelen(infos.ptr1);
			(free(infos.ptr1), free(infos.ptr2));
		}
		else
			infos.res++;
	}
	return (infos.res);
}

void	handle_var(char *str, t_int_tab *infos, t_list *envp, t_main_envp *imp)
{
	char	*temp;

	infos->ptr2 = get_var_str(str + infos->i + 1);
	temp = parse_var(infos->ptr2, envp, imp);
	ft_memcpy(infos->ptr1 + infos->res, temp, ft_securelen(temp));
	infos->res += ft_securelen(temp);
	infos->i += ft_securelen(infos->ptr2) + (infos->ptr2[0] == '(');
	free(temp);
	free(infos->ptr2);
}

char	*parse_quotes(char *str, t_list *envp, t_main_envp *imp)
{
	t_int_tab	infos;

	infos.ptr1 = malloc(sizeof(char) * (1 + get_parsed_len(str, envp, imp)));
	if (!infos.ptr1)
		return (NULL);
	infos.i = -1;
	infos.res = 0;
	infos.cur_quote = 0;
	infos.backslash = 0;
	while (str[++infos.i])
	{
		if (!check_special_char(str[infos.i], &infos.backslash,
				&infos.cur_quote))
			continue ;
		if ((infos.cur_quote != '\'') && (str[infos.i] == '$')
			&& (!infos.backslash))
			handle_var(str, &infos, envp, imp);
		else
			infos.ptr1[infos.res++] = str[infos.i];
	}
	infos.ptr1[infos.res] = 0;
	printf("Before : |%s|\nAfter : |%s|\n", str, infos.ptr1);
	free(str);
	return (infos.ptr1);
}
