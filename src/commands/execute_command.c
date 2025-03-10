/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:04:40 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/10 17:30:12 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_builtins(int code, t_command *cmd)
{
	if (code == 1)
		ms_echo(cmd);
	else if (code == 2)
		ms_cd(cmd);
	else if (code == 3)
		ms_pwd();
	else if (code == 4)
		ms_export(cmd);
	else if (code == 5)
		ms_unset(cmd);
	else if (code == 6)
		ms_env(cmd);
	else if (code == 7)
		ms_exit(cmd);
}

void	execute_child_cmd(t_command cmd, int pipes[2], int temp)
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

void	execute_last_cmd(t_command cmd, int pipes[2])
{
	int			code;

	close(pipes[1]);
	dup2(pipes[0], 0);
	code = check_builtins(cmd.argv[0]);
	if (code)
		handle_builtins(code, &cmd);
	else
		execute_bin(cmd.argv, cmd.imp);
	exit(0);
}

char	*execute_single_command(t_list *commands, t_list **envp,
		t_main_envp *imp)
{
	int			code;
	pid_t		pid;
	t_command	cmd;

	pid = fork();
	if (!pid)
	{
		cmd.imp = imp;
		cmd.envp = envp;
		cmd.argv = (char **)commands->content;
		code = check_builtins(cmd.argv[0]);
		if (code)
			handle_builtins(code, &cmd);
		else
			execute_bin(cmd.argv, cmd.imp);
	}
	waitpid(pid, NULL, 0);
	return (NULL);
}

char	*execute_line(t_list *commands, t_list **envp, t_main_envp *imp)
{
	t_int_tab	itab;
	pid_t		pid;
	int			pipes[2];

	itab = init_int_tab();
	itab.res = ft_lstsize(commands);
	if (itab.res == 1)
		return (execute_single_command(commands, envp, imp));
	itab.ret = 0;
	while (++itab.i < itab.res)
	{
		if ((itab.i + 1) != itab.res)
			if (pipe(pipes) < 0)
				return (NULL);
		pid = fork();
		if (pid < 0)
			return (NULL);
		if (!pid && ((itab.i + 1) != itab.res))
			execute_child_cmd(make_cmd(commands->content, envp, imp),
				pipes, itab.ret);
		else if (!pid)
			execute_last_cmd(make_cmd(commands->content, envp, imp), pipes);
		goto_next_command(&commands, &itab.ret, pipes);
	}
	return (wait_line_exec_end(itab.res, itab.ret, pipes[0]));
}
