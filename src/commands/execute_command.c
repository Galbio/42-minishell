/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:04:40 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/09 20:19:45 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_single_bin(t_cmd_params *cmd)
{
	pid_t		pid;
	int			stat;

	pid = fork();
	if (pid < 0)
		return (1);
	set_exit_status(1);
	if (!pid)
		execute_bin(cmd);
	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	return (get_exit_status());
}

static void	manage_saves(int saves[3], char mode)
{
	if (mode == 0)
	{
		saves[0] = dup(0);
		saves[1] = dup(1);
		saves[2] = dup(2);
		return ;
	}
	dup2(saves[0], 0);
	dup2(saves[1], 1);
	dup2(saves[2], 2);
}

static int	execute_single_command(t_cmd_params *cmd)
{
	int			temp;
	int			res;
	int			saves[3];

	if (ft_isonlywhitespaces(cmd->argv[0]))
	{
		free_cmd(cmd, 'c');
		free(cmd);
		return (0);
	}
	manage_saves(saves, 0);
	res = get_exit_status();
	dup2(cmd->imp->output_fd, 1);
	dup2(cmd->imp->input_fd, 0);
	if (handle_redirections(cmd))
		return (2);
	temp = check_builtins(cmd->argv[0]);
	if (!temp)
		res = execute_single_bin(cmd);
	else
		res = handle_builtins(temp, cmd);
	manage_saves(saves, 1);
	free_cmd(cmd, 'c');
	free(cmd);
	return (res);
}

int	execute_command(t_list *commands, t_cmd_params *params,
		t_list *cmd_lst, t_list *sep)
{
	params->pipes = commands;
	params->cmds = cmd_lst;
	params->sep = sep;
	if (commands && !commands->next)
	{
		if (((char *)(commands->content))[0] == '(')
		{
			params->argv = (char **)(&(commands->content));
			return (execute_subshell(params));
		}
		else
		{
			params->argv = (char **)(&(commands->content));
			params = create_command_argv(params);
			return (execute_single_command(params));
		}
	}
	return (execute_pipes(params));
}
