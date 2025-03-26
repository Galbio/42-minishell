/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:20:49 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/26 20:56:48 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_pipe_cmd(t_cmd_params *cmd, int pipes[2], int last, t_list *cmd_lst)
{
	int		res;

	ft_lstclear(&cmd_lst, free);
	close(pipes[last]);
	if (!cmd->argv[0][0])
	{
		close(pipes[!last]);
		res = cmd->imp->exit_status;
		free_cmd(cmd, 1);
		exit(res);
	}
	cmd->imp->input_fd = ((pipes[0] * last) + (cmd->imp->input_fd * !last));
	cmd->imp->output_fd = ((cmd->imp->output_fd * last) + (pipes[1] * !last));
	cmd->imp->is_bquoted++;
	execute_line(cmd->argv[0], cmd->envp, cmd->imp);
	cmd->imp->is_bquoted--;
	res = cmd->imp->exit_status;
	free_cmd(cmd, 1);
	exit(res);
}

int	execute_pipes(t_list *commands, t_cmd_params *cmd, t_list *cmd_lst)
{
	t_int_tab	itab;
	int			pipes[2];
	pid_t		pid;

	itab = init_int_tab();
	itab.res = ft_lstsize(commands);
	while (++itab.i < itab.res)
	{
		if ((itab.i + 1) != itab.res)
			if (pipe(pipes) < 0)
				return (1);
		pid = fork();
		if (pid < 0)
			return (1);
		cmd->argv = (char **)(&(commands->content));
		if (!pid)
			execute_pipe_cmd(cmd, pipes, (itab.i + 1) == itab.res, cmd_lst);
		go_to_next_command(&commands, &(cmd->imp->input_fd), pipes);
	}
	return (wait_line_end_exec(itab.res, cmd->imp->input_fd, pipes[0], pid));
}
