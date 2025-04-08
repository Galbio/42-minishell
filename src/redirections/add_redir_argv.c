/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redir_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:20:19 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/08 23:15:15 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_redirect_text(char *str)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(str, &itab);
		if (!itab.backslash && !itab.cur_quote
			&& ft_strchr(" \n\t", str[itab.i]))
			return (ft_substr(str, 0, itab.i));
		if (!itab.backslash && !itab.cur_quote && (str[itab.i] == '$'))
			itab.i += go_to_var_end(str + itab.i) - 1;
	}
	return (ft_substr(str, 0, itab.i));
}

static void	add_method(char *str, t_int_tab *itab, t_cmd_params *cmd)
{
	int		i;
	int		j;

	i = 0;
	if (itab->i && (str[itab->i - 1] == '&'))
		i = 1;
	else if (itab->i)
		while ((itab->i - i) && ft_isdigit(str[itab->i - i - 1]))
			i++;
	j = 0;
	while (str[itab->i + j] && ft_strchr("<>", str[itab->i + j]))
		j++;
	if ((j == 2) && (str[itab->i + 2] == '-')
		&& !ft_strncmp("<<", str + itab->i, 2))
		j++;
	ft_lstadd_back(&(cmd->redir), ft_lstnew(
			ft_substr(str + itab->i - i, 0, j + i)));
	itab->i += j;
}

static void	add_value(char **argv, char is_fd, t_cmd_params *cmd)
{
	t_list	*end;

	end = ft_lstlast(cmd->redir);
	if (is_fd)
		end->next = ft_lstnew((void *)1);
	else
		end->next = ft_lstnew((void *)0);
	end->next->next = ft_lstnew(argv);
}

static void	parse_redirect_value(char *str, t_int_tab *itab,
		t_cmd_params *cmd, char value_is_fd)
{
	char	*to_add;

	to_add = get_redirect_text(str + itab->i);
	itab->i += ft_strlen(to_add);
	add_value(fill_return_argv(cmd, fill_argv(to_add, cmd)), value_is_fd, cmd);
	itab->ret = itab->i;
}

void	add_redirection(char *str, t_int_tab *itab,
		t_cmd_params *cmd, t_list **dest)
{
	char	value_is_fd;

	if (itab->i && ((str[itab->i - 1] == '&') || ft_isdigit(str[itab->i - 1])))
		;
	else if (itab->i && !ft_strchr(" \t\n", str[itab->i - 1]))
	{
		add_to_argv(dest, str, itab, cmd);
		itab->i++;
	}
	add_method(str, itab, cmd);
	value_is_fd = 0;
	if ((str[itab->i] == '&') && is_only_nb(str + itab->i + 1))
	{
		value_is_fd++;
		itab->i++;
	}
	while (str[itab->i] && ft_strchr(" \n\t", str[itab->i]))
		itab->i++;
	parse_redirect_value(str, itab, cmd, value_is_fd);
}
