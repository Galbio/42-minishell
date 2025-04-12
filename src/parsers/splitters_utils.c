/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitters_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:54:49 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/12 15:48:45 by lroussel         ###   ########.fr       */
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

int	add_cmd(char *str, t_list **dest, t_int_tab *itab)
{
	char	*temp;

	temp = ft_substr(str, itab->ret, itab->i - itab->ret);
	if (!ft_strncmp(str + itab->i, ";;", 2) || ft_isonlywhitespaces(temp)
		|| ft_isonlywhitespaces(str + itab->i))
	{
		free(temp);
		token_error(str);
		return (1);
	}
	ft_lstadd_back(dest, ft_lstnew(trim_ws(temp)));
	itab->ret = (itab->i + 1 + (str[itab->i] != ';'));
	if (!str[itab->ret - 1])
		itab->ret--;
	if (!str[itab->ret] || ft_strchr("|&", str[itab->ret]))
	{
		if (str[itab->ret])
			itab->i += 2;
		token_error(str);
		return (1);
	}
	itab->i += (str[itab->i] != ';');
	return (0);
}
