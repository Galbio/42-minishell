/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_names_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:16:32 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/07 21:59:25 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	go_to_cmd_end(char *str)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(str, &itab);
		if (!itab.backslash && (str[itab.i] == '$')
			&& (itab.cur_quote != '\''))
			itab.i += go_to_var_end(str + itab.i) - 1;
		else if (!itab.backslash && !itab.cur_quote && (str[itab.i] == '('))
			itab.ret++;
		else if (!itab.backslash && !itab.cur_quote && (str[itab.i] == ')'))
			itab.ret--;
		if (!itab.ret)
			return (itab.i + 1);
	}
	return (itab.i);
}

int	go_to_var_end(char *str)
{
	int		i;

	if (str[0] == '(')
		return (go_to_cmd_end(str));
	if (str[1] == '(')
		return (go_to_cmd_end(str + 1) + 1);
	if (ft_strchr("?#", str[1]) || ft_isdigit(str[1]))
		return (2);
	i = 0;
	while (str[++i])
		if ((str[i] != '_') && !ft_isalnum(str[i]))
			return (i);
	return (i);
}

char	*get_var_name(char *str)
{
	int		i;

	if (ft_isdigit(*str))
		return (ft_itoa(*str + '0'));
	if (*str == '?')
		return (ft_strdup("?"));
	if (*str == '#')
		return (ft_strdup("#"));
	i = -1;
	while (str[++i])
		if ((str[i] != '_') && !ft_isalnum(str[i]))
			return (ft_substr(str, 0, i));
	return (ft_substr(str, 0, i + 1));
}
