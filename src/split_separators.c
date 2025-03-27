/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_separators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:39:43 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 04:49:21 by gakarbou         ###   ########.fr       */
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

t_list	*init_pipes(char *str)
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

char	is_sep(char *str, t_list **sep)
{
	if (*str == ';')
	{
		ft_lstadd_back(sep, ft_lstnew(ft_strdup(";")));
		return (1);
	}
	if (!ft_strncmp(str, "||", 2))
	{
		ft_lstadd_back(sep, ft_lstnew(ft_strdup("|")));
		return (1);
	}
	if (!ft_strncmp(str, "&&", 2))
	{
		ft_lstadd_back(sep, ft_lstnew(ft_strdup("&")));
		return (1);
	}
	return (0);
}

static void	add_cmd(char *str, t_list **dest, t_int_tab *itab)
{
	ft_lstadd_back(dest, ft_lstnew(trim_ws(
				ft_substr(str, itab->ret, itab->i - itab->ret))));
	itab->ret = itab->i + 1;
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
			&& is_sep(str + itab.i, sep))
			add_cmd(str, &dest, &itab);
	}
	if (str[itab.ret])
		ft_lstadd_back(&dest, ft_lstnew(
				trim_ws(ft_substr(str, itab.ret, itab.i))));
	return (dest);
}
