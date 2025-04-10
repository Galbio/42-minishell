/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitters_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:54:49 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/11 01:54:18 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *str, t_int_tab *itab)
{
	write(2, "minishell: syntax error", 23);
	if (str[itab->ret])
	{
		write(2, " near unexpected token `", 24);
		write(2, str + itab->i, 1 + (str[itab->i + 1] == str[itab->i]));
		write(2, "'\n", 2);
	}
	else
		write(2, ": unexpected end of file\n", 25);
	set_exit_status(258);
}

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
	if (ft_isonlywhitespaces(temp) || ft_isonlywhitespaces(str + itab->i))
	{
		free(temp);
		print_error(str, itab);
		return (1);
	}
	ft_lstadd_back(dest, ft_lstnew(trim_ws(temp)));
	itab->ret = (itab->i + 1 + (str[itab->i] != ';'));
	if (!str[itab->ret - 1])
		itab->ret--;
	if (!str[itab->ret])
	{
		print_error(str, itab);
		return (1);
	}
	itab->i += (str[itab->i] != ';');
	return (0);
}
