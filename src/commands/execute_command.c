/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:04:40 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/26 14:33:35 by gakarbou         ###   ########.fr       */
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
	if (!pid)
		execute_bin(cmd);
	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	return (1);
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
		return (0);
	manage_saves(saves, 0);
	res = cmd->imp->exit_status;
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
	temp = -1;
	while (cmd->argv[++temp])
		free(cmd->argv[temp]);
	free(cmd->argv);
	return (res);
}

int	execute_command(t_list *commands, t_list **envp, t_main_envp *imp)
{
	if (commands && !commands->next)
	{
		if (((char *)(commands->content))[0] == '(')
			return (execute_subshell((char *)commands->content, envp, imp));
		return (execute_single_command(create_command_argv(make_cmd(
						&commands->content, envp, imp))));
	}
	return (execute_pipes(commands, make_cmd(NULL, envp, imp)));
}
