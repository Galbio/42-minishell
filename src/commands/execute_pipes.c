/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:20:49 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/12 21:30:03 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child_cmd(t_cmd_params cmd, int pipes[2], int temp)
{
	int			code;

	close(pipes[0]);
	dup2(temp, 0);
	dup2(pipes[1], 1);
	code = check_builtins(cmd.argv[0]);
	if (code)
		handle_builtins(code, &cmd);
	else
		execute_bin(cmd.argv, cmd.imp);
	exit(0);
}

static void	execute_last_cmd(t_cmd_params cmd, int pipes[2])
{
	int			code;

	close(pipes[1]);
	dup2(pipes[0], 0);
	dup2(cmd.imp->output_fd, 1);
	code = check_builtins(cmd.argv[0]);
	if (code)
		handle_builtins(code, &cmd);
	else
		execute_bin(cmd.argv, cmd.imp);
	exit(0);
}

void	execute_pipes(t_list *commands, t_list **envp, t_main_envp *imp)
{
	t_int_tab	itab;
	int			pipes[2];
	pid_t		pid;

	itab = init_int_tab();
	itab.res = ft_lstsize(commands);
	itab.ret = 0;
	while (++itab.i < itab.res)
	{
		if ((itab.i + 1) != itab.res)
			if (pipe(pipes) < 0)
				return ;
		pid = fork();
		if (pid < 0)
			return ;
		if (!pid && ((itab.i + 1) != itab.res))
			execute_child_cmd(make_cmd(commands->content, envp, imp),
				pipes, itab.ret);
		else if (!pid)
			execute_last_cmd(make_cmd(commands->content, envp, imp), pipes);
		go_to_next_command(&commands, &itab.ret, pipes);
	}
	wait_line_end_exec(itab.res, itab.ret, pipes[0]);
}
