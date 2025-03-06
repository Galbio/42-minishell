/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:04:40 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/06 15:18:03 by gakarbou         ###   ########.fr       */
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

char	check_builtins(char *name)
{
	char		*temp;

	temp = ft_strrchr(name, '/');
	if (temp)
		name = temp + 1;
	if (!ft_strncmp(name, "echo", 5))
		return (1);
	else if (!ft_strncmp(name, "cd", 3))
		return (2);
	else if (!ft_strncmp(name, "pwd", 4))
		return (3);
	else if (!ft_strncmp(name, "export", 7))
		return (4);
	else if (!ft_strncmp(name, "unset", 6))
		return (5);
	else if (!ft_strncmp(name, "env", 4))
		return (6);
	else if (!ft_strncmp(name, "exit", 5))
		return (7);
	return (0);
}

void	execute_child_cmd(char **argv, t_list **envp,
		t_main_envp *imp, int pipes[2])
{
	t_command	cmd;
	int			code;

	cmd.imp = imp;
	cmd.envp = envp;
	cmd.argv = argv;
	close(pipes[0]);
	dup2(pipes[1], 1);
	code = check_builtins(argv[0]);
	if (code)
		handle_builtins(code, &cmd);
	else
		execute_bin(argv, imp);
	exit(0);
}

void	execute_last_cmd(char **argv, t_list **envp,
		t_main_envp *imp, int pipes[2])
{
	t_command	cmd;
	int			code;

	cmd.imp = imp;
	cmd.envp = envp;
	cmd.argv = argv;
	close(pipes[1]);
	dup2(pipes[0], 0);
	code = check_builtins(argv[0]);
	if (code)
		handle_builtins(code, &cmd);
	else
		execute_bin(argv, imp);
	exit(0);
}

char	*execute_single_command(t_list *commands, t_list **envp, t_main_envp *imp)
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
			execute_bin(cmd.argv, imp);
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
	itab.ret = ft_lstsize(commands);
	if (itab.ret == 1)
		return (execute_single_command(commands, envp, imp));
	itab.i++;
	while (++itab.i <= itab.ret)
	{
		if (itab.i < itab.ret)
			if (pipe(pipes) < 0)
				return (NULL);
		pid = fork();
		if (pid < 0)
			return (NULL);
		if (!pid && (itab.i < itab.ret))
			execute_child_cmd((char **)commands->content, envp, imp, pipes);
		else if (!pid)
		{
			execute_last_cmd((char **)commands->content, envp, imp, pipes);
		}
		close(pipes[1]);
		close(pipes[0]);
		commands = commands->next;
	}
	int i, stat, ret;
	i = -1;
	while (++i < itab.ret)
	{
		ret = wait(&stat);
	}
	return (NULL);
}
