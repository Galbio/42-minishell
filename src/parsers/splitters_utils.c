/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitters_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:54:49 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/14 08:11:42 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(char *str, t_int_tab *itab)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	if (!str[itab->i])
		write(2, "newline", 7);
	else
	{
		if (!ft_strncmp("&|", str + itab->i, 2))
			write(2, "|", 1);
		else if (!ft_strncmp("|&", str + itab->i, 2))
			write(2, "|&", 2);
		else
			write(2, str + itab->i, 1 + (str[itab->i + 1] == str[itab->i]));
	}
	write(2, "'\n", 2);
	if (!isatty(STDIN_FILENO))
	{
		write(2, " `", 2);
		write(2, str, ft_strlen(str));
		write(2, "'\n", 2);
	}
	set_exit_status(258);
	return (1);
}

int	handle_separator(char *str, t_list **sep, int i)
{
	if (str[i] == ';')
	{
		ft_lstadd_back(sep, ft_lstnew(ft_strdup(";")));
		return (1);
	}
	if (!ft_strncmp(str + i, "||", 2))
	{
		ft_lstadd_back(sep, ft_lstnew(ft_strdup("|")));
		return (1);
	}
	if (!ft_strncmp(str + i, "&&", 2))
	{
		ft_lstadd_back(sep, ft_lstnew(ft_strdup("&")));
		return (1);
	}
	if (!ft_strncmp(str + i, "|&", 2) || !ft_strncmp(str + i, "&|", 2))
		return (1);
	if ((str[i] == '&') && !i)
		return (1);
	if ((str[i] == '&') && !((str[i + 1] == '>') || (str[i - 1] == '>')))
		return (1);
	return (0);
}

int	add_cmd(char *str, t_list **dest, t_int_tab *itab, int is_pipe)
{
	char	*temp;

	temp = ft_substr(str, itab->ret, itab->i - itab->ret);
	if (!ft_strncmp(str + itab->i, ";;", 2) || ft_isonlywhitespaces(temp)
		|| ft_isonlywhitespaces(str + itab->i))
	{
		free(temp);
		return (print_error(str, itab));
	}
	else if ((str[itab->i] != ';') && (str[itab->i] != '|' && !is_pipe)
		&& (str[itab->i] != str[itab->i + 1]))
	{
		free(temp);
		return (print_error(str, itab));
	}
	ft_lstadd_back(dest, ft_lstnew(trim_ws(temp)));
	itab->ret = (itab->i + 1 + (str[itab->i] != ';'));
	itab->i += (str[itab->i] != ';') + 1;
	if (!str[itab->ret - 1])
		itab->ret--;
	if ((!str[itab->ret] || ft_strchr("|&", str[itab->ret])) && !ft_strchr("<>", str[0]))
		return (print_error(str, itab));
	itab->i--;
	return (0);
}
