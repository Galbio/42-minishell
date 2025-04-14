/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 08:35:44 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/14 05:05:22 by gakarbou         ###   ########.fr       */
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

static char	init_execute_line(char *str, char *sep,
		t_list **sep_list, t_list **cmd_list)
{
	if (ft_isonlywhitespaces(str))
	{
		free(str);
		return (1);
	}
	*sep_list = NULL;
	*sep = ';';
	*cmd_list = split_separators(str, sep_list);
	free(str);
	return (0);
}

void	execute_line(char *str, t_list **envp, t_main_envp *imp)
{
	t_list			*commands_list;
	t_list			*cur_commands;
	t_list			*sep;
	char			cur_sep;
	int				status;

	if (init_execute_line(str, &cur_sep, &sep, &commands_list))
		return ;
	while (commands_list)
	{
		if (commands_list->content)
		{
			status = get_exit_status();
			if ((status < 256) && (((cur_sep == '|') && status)
					|| ((cur_sep == '&') && !status) || (cur_sep == ';')))
			{
				cur_commands = split_pipes((char *)commands_list->content);
				set_exit_status(execute_command(cur_commands, make_cmd(
							NULL, envp, imp), commands_list, sep));
			}
		}
		cur_sep = go_to_next_cmd(&sep, &commands_list);
	}
	ft_lstclear(&sep, free);
}
