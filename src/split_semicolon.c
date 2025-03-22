/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:01:11 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/22 17:14:55 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*split_semicolon(char *str)
{
	t_list		*dest;
	t_int_tab	itab;

	itab = init_int_tab();
	dest = NULL;
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(str, &itab);
		if (str[itab.i] == '$' && !itab.backslash && !itab.cur_quote)
			itab.i += go_to_var_end(str + itab.i) - 1;
		else if ((str[itab.i] == ';') && !itab.backslash && !itab.cur_quote)
		{
			itab.ptr1 = ft_substr(str, itab.ret, itab.i - itab.ret);
			itab.ret = itab.i + 1;
			ft_lstadd_back(&dest, ft_lstnew(trim_ws(itab.ptr1)));
		}
	}
	if (!str[itab.ret])
		return (dest);
	itab.ptr1 = ft_substr(str, itab.ret, itab.i);
	ft_lstadd_back(&dest, ft_lstnew(trim_ws(itab.ptr1)));
	return (dest);
}
