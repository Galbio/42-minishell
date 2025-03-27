/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:35:44 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 00:17:17 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	go_to_next_cmd(t_list **sep, t_list **cmd_list)
{
	char	next_sep;
	t_list	*tmp;

	next_sep = ';';
	if (*sep)
	{
		tmp = *sep;
		next_sep = ((char *)(tmp->content))[0];
		*sep = tmp->next;
		free(tmp->content);
		free(tmp);
	}
	tmp = *cmd_list;
	*cmd_list = tmp->next;
	free(tmp->content);
	free(tmp);
	return (next_sep);
}

void	execute_line(char *str, t_list **envp, t_main_envp *imp)
{
	t_list	*commands_list;
	t_list	*cur_commands;
	t_list	*sep;
	char	cur_sep;

	if (ft_isonlywhitespaces(str))
	{
		free(str);
		return ;
	}
	sep = NULL;
	cur_sep = ';';
	commands_list = split_separators(str, &sep);
	free(str);
	while (commands_list)
	{
		if (((cur_sep == '|') && imp->exit_status) || ((cur_sep == '&')
				&& !imp->exit_status) || (cur_sep == ';'))
		{
			cur_commands = init_pipes((char *)commands_list->content);
			imp->exit_status = execute_command(cur_commands, envp, imp, commands_list);
		}
		cur_sep = go_to_next_cmd(&sep, &commands_list);
	}
}
