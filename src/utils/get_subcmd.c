/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_subcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:21:27 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/07 21:50:11 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_closing_bracket(char bracket, char c)
{
	if (bracket == '(')
		return (c == ')');
	else if (bracket == '{')
		return (c == '}');
	else if (bracket == '[')
		return (c == ']');
	return (0);
}

int	get_subcmd_size(char *str)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(str, &itab);
		if (itab.i && !itab.cur_quote && !itab.backslash
			&& ft_strchr("([{", str[itab.i]))
			itab.i += get_subcmd_size(str + itab.i) - 1;
		else if (!itab.backslash && !itab.cur_quote
			&& is_closing_bracket(*str, str[itab.i]))
			return (itab.i + 1);
		else if (!itab.backslash && (itab.cur_quote != '\'')
			&& (str[itab.i] == '$') && str[itab.i + 1]
			&& ft_strchr("({", str[itab.i + 1]))
			itab.i += get_subcmd_size(str + itab.i + 1);
	}
	return (itab.i);
}

char	*get_subcmd(char *str)
{
	return (ft_substr(str, 1, get_subcmd_size(str) - 2));
}
