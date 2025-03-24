/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:04:40 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/24 18:05:31 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_single_bin(t_cmd_params cmd)
{
	pid_t		pid;
	int			stat;

	pid = fork();
	if (pid < 0)
		return (1);
	if (!pid)
		execute_bin(cmd.argv, cmd.imp);
	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	return (1);
}

static int	execute_single_command(t_cmd_params cmd)
{
	int			temp;
	int			res;

	res = cmd.imp->exit_status;
	dup2(cmd.imp->output_fd, 1);
	dup2(cmd.imp->input_fd, 0);
	temp = check_builtins(cmd.argv[0]);
	if (!temp)
		res = execute_single_bin(cmd);
	else
		res = handle_builtins(temp, &cmd);
	temp = -1;
	while (cmd.argv[++temp])
		free(cmd.argv[temp]);
	free(cmd.argv);
	return (res);
}

static int	execute_command(t_list *commands, t_list **envp, t_main_envp *imp)
{
	if (commands && !commands->next)
	{
		if (((char *)(commands->content))[0] == '(')
			return (execute_subshell((char *)commands->content, envp, imp));
		return (execute_single_command(make_cmd(create_command_argv(
						commands->content, envp, imp), envp, imp)));
	}
	return (execute_pipes(commands, envp, imp));
}

static char	go_to_next_cmd(t_list **sep, t_list **cur_cmds, t_list **cmd_list)
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
	ft_lstclear(cur_cmds, free);
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

	sep = NULL;
	cur_sep = ';';
	commands_list = split_separators(str, &sep);
	while (commands_list)
	{
		if (((cur_sep == '|') && imp->exit_status) || ((cur_sep == '&')
				&& !imp->exit_status) || (cur_sep == ';'))
		{
			cur_commands = init_pipes((char *)commands_list->content);
			imp->exit_status = execute_command(cur_commands, envp, imp);
		}
		cur_sep = go_to_next_cmd(&sep, &cur_commands, &commands_list);
	}
}
