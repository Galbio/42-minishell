/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:04:40 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/24 02:02:56 by gakarbou         ###   ########.fr       */
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
	if (temp)
		res = handle_builtins(temp, &cmd);
	else
		res = execute_single_bin(cmd);
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

void	execute_line(t_list *commands_list, t_list **envp, t_main_envp *imp)
{
	t_list	*cur_commands;
	t_list	*temp;

	while (commands_list)
	{
		cur_commands = init_pipes((char *)commands_list->content);
		imp->exit_status = execute_command(cur_commands, envp, imp);
		ft_lstclear(&cur_commands, free);
		temp = commands_list;
		commands_list = commands_list->next;
		free(temp->content);
		free(temp);
	}
}
