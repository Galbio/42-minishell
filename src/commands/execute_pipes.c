/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:20:49 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/23 14:58:10 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_pipe_cmd(t_cmd_params cmd, int pipes[2], int last)
{
	int		res;

	close(pipes[last]);
	if (!cmd.argv[0][0])
	{
		close(pipes[!last]);
		free_envp(cmd.envp, cmd.imp);
		exit(cmd.imp->exit_status);
	}
	res = 0;
	dup2((pipes[0] * last) + (cmd.imp->input_fd * !last), 0);
	dup2((cmd.imp->output_fd * last) + (pipes[1] * !last), 1);
	cmd.imp->is_bquoted++;
	execute_line(split_semicolon(cmd.argv[0]), cmd.envp, cmd.imp);
	cmd.imp->is_bquoted--;
	free_envp(cmd.envp, cmd.imp);
	exit(res);
}

int	execute_pipes(t_list *commands, t_list **envp, t_main_envp *imp)
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
		if (!pid)
			execute_pipe_cmd(make_cmd(&(commands->content), envp, imp),
				pipes, (itab.i + 1) == itab.res);
		go_to_next_command(&commands, &imp->input_fd, pipes);
	}
	return (wait_line_end_exec(itab.res, imp->input_fd, pipes[0], pid));
}
