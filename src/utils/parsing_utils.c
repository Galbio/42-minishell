/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:51:10 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/27 21:41:54 by gakarbou         ###   ########.fr       */
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
	int		pare_count;

	i = -1;
	pare = (str[0] == '(');
	pare_count = 0;
	while (str[++i])
	{
		if ((str[i] != '_') && (!ft_isalnum(str[i])) && (!pare))
			return (ft_substr(str, 0, i));
		else if (str[i] == '(')
			pare_count++;
		else if (str[i] == ')')
			pare_count--;
		if (pare && !pare_count)
			return (ft_substr(str, 0, i + 1));
	}
	return (ft_substr(str, 0, i + 1));
}

void	handle_var(char *str, t_int_tab *infos, t_list **envp, t_main_envp *imp)
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
