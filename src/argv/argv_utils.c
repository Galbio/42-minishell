/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:57:20 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/17 21:02:32 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_quotes(char *str)
{
	char		*dest;
	t_int_tab	itab;

	itab = init_int_tab();
	itab.ret = get_parsed_size(str);
	dest = malloc(sizeof(char) * (itab.ret + 1));
	if (!dest)
		return (NULL);
	dest[itab.ret] = 0;
	while (str[++itab.i])
	{
		if (!check_special_char(str[itab.i], &itab.backslash, &itab.cur_quote))
			continue ;
		dest[itab.res++] = str[itab.i];
	}
	free(str);
	return (dest);
}

static char	*get_var_name(char *str)
{
	int		pare;
	int		pare_count;
	int		i;

	if (ft_isdigit(*str))
		return (ft_itoa(*str + '0'));
	else if (*str == '?')
		return (ft_strdup("?"));
	pare = *str == '(';
	pare_count = 0;
	i = -1;
	while (str[++i])
	{
		if (!pare && (str[i] != '_') && !ft_isalnum(str[i]))
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

int	get_parsed_size(char *str)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (str[++itab.i])
	{
		if (!check_special_char(str[itab.i], &itab.backslash, &itab.cur_quote))
			continue ;
		itab.res++;
	}
	return (itab.res);
}

void	add_to_argv(t_list **dest, char *str, t_int_tab *itab)
{
	if (str[itab->ret])
	{
		ft_lstadd_front(dest, ft_lstnew(parse_quotes(
					ft_substr(str, itab->ret, itab->i - itab->ret))));
		itab->ret = itab->i + 1;
	}
}

void	add_var_to_argv(t_list **dest, char *str, t_int_tab *itab,
		t_cmd_params cmd)
{
	itab->ptr1 = get_var_name(str + itab->i + 1);
	handle_var(dest, cmd.envp, cmd.imp, itab);
	go_to_var_end(str, &itab->i);
	free(itab->ptr1);
	itab->ret = itab->i + 1;
}
