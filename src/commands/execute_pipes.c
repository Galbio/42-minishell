/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:20:49 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/17 17:10:35 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child_cmd(t_cmd_params cmd, int pipes[2], int temp)
{
	int			code;
	int			res;

	close(pipes[0]);
	if (!cmd.argv[0][0])
	{
		close(pipes[1]);
		free_envp(cmd.envp, cmd.imp);
		exit(cmd.imp->exit_status);
	}
	res = 0;
	dup2(temp, 0);
	dup2(pipes[1], 1);
	code = check_builtins(cmd.argv[0]);
	if (code)
		res = handle_builtins(code, &cmd);
	else
		execute_bin(cmd.argv, cmd.imp);
	free_envp(cmd.envp, cmd.imp);
	exit(res);
}

static void	execute_last_cmd(t_cmd_params cmd, int pipes[2])
{
	int			code;
	int			res;

	close(pipes[1]);
	if (!cmd.argv[0][0])
	{
		close(pipes[0]);
		free_envp(cmd.envp, cmd.imp);
		exit(cmd.imp->exit_status);
	}
	res = 0;
	dup2(pipes[0], 0);
	dup2(cmd.imp->output_fd, 1);
	code = check_builtins(cmd.argv[0]);
	if (code)
		res = handle_builtins(code, &cmd);
	else
		execute_bin(cmd.argv, cmd.imp);
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
	itab.ret = 0;
	while (++itab.i < itab.res)
	{
		if ((itab.i + 1) != itab.res)
			if (pipe(pipes) < 0)
				return (1);
		pid = fork();
		if (pid < 0)
			return (1);
		if (!pid && ((itab.i + 1) != itab.res))
			execute_child_cmd(make_cmd(commands->content, envp, imp),
				pipes, itab.ret);
		else if (!pid)
			execute_last_cmd(make_cmd(commands->content, envp, imp), pipes);
		go_to_next_command(&commands, &itab.ret, pipes);
	}
	return (wait_line_end_exec(itab.res, itab.ret, pipes[0], pid));
}
