/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 03:38:49 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/23 15:08:19 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*init_pipes(char *str)
{
	t_int_tab	itab;
	t_list		*cmds;

	itab = init_int_tab();
	cmds = NULL;
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(str, &itab);
		if (!itab.backslash && !itab.cur_quote && ft_strchr("$(", str[itab.i]))
			itab.i += go_to_var_end(str + itab.i) - 1;
		if ((str[itab.i] == '|') && !itab.backslash && !itab.cur_quote
			&& (str[itab.i + 1] != '|'))
		{
			itab.ptr1 = ft_substr(str, itab.ret, itab.i - itab.ret);
			itab.ret = itab.i + 1;
			ft_lstadd_back(&cmds, ft_lstnew(trim_ws(itab.ptr1)));
		}
	}
	if (!str[itab.ret])
		return (cmds);
	itab.ptr1 = ft_substr(str, itab.ret, itab.i);
	ft_lstadd_back(&cmds, ft_lstnew(trim_ws(itab.ptr1)));
	return (cmds);
}
