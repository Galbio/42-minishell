/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitters_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:54:49 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/08 17:28:50 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_separator(char *str, t_list **sep)
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

void	add_cmd(char *str, t_list **dest, t_int_tab *itab)
{
	ft_lstadd_back(dest, ft_lstnew(trim_ws(
				ft_substr(str, itab->ret, itab->i - itab->ret))));
	itab->ret = itab->i + 1;
}
