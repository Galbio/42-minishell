/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:39:43 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/04 14:36:41 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	go_to_subcmd_end(char *str)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(str, &itab);
		if (itab.backslash || itab.cur_quote)
			continue ;
		if (str[itab.i] == ')')
			itab.ret--;
		else if (str[itab.i] == '(')
			itab.ret++;
		if (!itab.ret)
			return (itab.i);
	}
	return (itab.i);
}

t_list	*split_pipes(char *str)
{
	t_int_tab	itab;
	t_list		*dest;

	itab = init_int_tab();
	dest = NULL;
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(str, &itab);
		if (!itab.backslash && !itab.cur_quote && (str[itab.i] == '$'))
			itab.i += go_to_var_end(str + itab.i) - 1;
		else if (!itab.backslash && !itab.cur_quote && (str[itab.i] == '('))
			itab.i += go_to_subcmd_end(str + itab.i);
		else if ((str[itab.i] == '|') && !itab.backslash && !itab.cur_quote
			&& (str[itab.i + 1] != '|'))
		{
			itab.ptr1 = ft_substr(str, itab.ret, itab.i - itab.ret);
			itab.ret = itab.i + 1;
			ft_lstadd_back(&dest, ft_lstnew(trim_ws(itab.ptr1)));
		}
	}
	if (!str[itab.ret])
		return (dest);
	ft_lstadd_back(&dest, ft_lstnew(trim_ws(ft_substr(str, itab.ret, itab.i))));
	return (dest);
}

t_list	*split_separators(char *str, t_list **sep)
{
	t_list		*dest;
	t_int_tab	itab;

	itab = init_int_tab();
	dest = NULL;
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(str, &itab);
		if (!itab.backslash && !itab.cur_quote && (str[itab.i] == '$'))
			itab.i += go_to_var_end(str + itab.i) - 1;
		else if (!itab.backslash && !itab.cur_quote && (str[itab.i] == '('))
			itab.i += go_to_subcmd_end(str + itab.i) - 1;
		else if (!itab.backslash && !itab.cur_quote
			&& handle_sep(str + itab.i, sep))
		{
			add_cmd(str, &dest, &itab);
			itab.ret += (str[itab.i] != ';');
		}
	}
	if (str[itab.ret])
		ft_lstadd_back(&dest, ft_lstnew(
				trim_ws(ft_substr(str, itab.ret, itab.i))));
	return (dest);
}

void	split_cmds(char *res, t_list **cmds)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (res[++itab.i])
	{
		itab.backslash = itab.i && (res[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(res, &itab);
		if (!itab.backslash && !itab.cur_quote && (res[itab.i] == '$'))
			itab.i += go_to_var_end(res + itab.i) - 1;
		else if (!itab.backslash && !itab.cur_quote && (res[itab.i] == '('))
			itab.i += go_to_subcmd_end(res + itab.i) - 1;
		if (!itab.cur_quote && (res[itab.i] == '\n'))
			add_cmd(res, cmds, &itab);
	}
	if (res[itab.ret])
		add_cmd(res, cmds, &itab);
}
