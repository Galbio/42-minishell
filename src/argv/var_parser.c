/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 03:46:01 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/17 20:55:29 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_commands(char *name, t_list **envp, t_main_envp *imp)
{
	t_list	*commands;
	int		old_redir;
	int		pipes[2];
	char	*dest;

	if (pipe(pipes) < 0)
		return (NULL);
	imp->is_bquoted++;
	old_redir = imp->output_fd;
	imp->output_fd = pipes[1];
	name[ft_strlen(name) - 1] = 0;
	commands = split_semicolon(name);
	execute_line(commands, envp, imp);
	imp->output_fd = old_redir;
	close(pipes[1]);
	imp->is_bquoted--;
	dest = ft_get_contents(pipes[0]);
	close(pipes[0]);
	return (clean_whitespaces(dest));
}

static char	*get_var_value(char *name, t_list *cur)
{
	int		len;
	char	*value;

	len = ft_strlen(name);
	while (cur)
	{
		value = (char *)cur->content;
		if ((value[len] == '=') && !ft_strncmp(name, value, len))
			return (ft_strdup(value + len + 1));
		cur = cur->next;
	}
	return (ft_strdup(""));
}

void	handle_var(t_list **dest, t_list **envp, t_main_envp *imp,
		t_int_tab *itab)
{
	char	*output;
	char	**splitted;
	int		i;

	if (itab->ptr1[0] == '?')
		output = ft_itoa((int)imp->exit_status);
	else if (itab->ptr1[0] == '(')
		output = handle_commands(itab->ptr1 + 1, envp, imp);
	else
		output = get_var_value(itab->ptr1, *envp);
	if (itab->cur_quote)
		ft_lstadd_front(dest, ft_lstnew(output));
	else
	{
		splitted = ft_split(output, 32);
		i = -1;
		while (splitted[++i])
			ft_lstadd_front(dest, ft_lstnew(splitted[i]));
		free(splitted);
	}
}
