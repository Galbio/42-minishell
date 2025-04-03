/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:20:49 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 07:10:37 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	go_to_next_command(t_list **commands, int *input_fd, int pipes[2])
{
	t_list	*temp;

	temp = *commands;
	*commands = (*commands)->next;
	free(temp->content);
	free(temp);
	if (*input_fd != 0)
		close(*input_fd);
	*input_fd = pipes[0];
	close(pipes[1]);
}

static int	wait_line_end_exec(int nb_cmd, int write_pipe,
		t_cmd_params *cmd, pid_t pid)
{
	int		i;
	int		stat;
	int		res;
	int		ret;

	if (cmd->imp->input_fd)
		close(cmd->imp->input_fd);
	close(write_pipe);
	i = -1;
	ret = 0;
	while (++i < nb_cmd)
	{
		res = wait(&stat);
		if (res == pid)
			if (WIFEXITED(stat))
				ret = WEXITSTATUS(stat);
	}
	free_cmd(cmd, 'c');
	free(cmd);
	return (ret);
}

static void	handle_pipe_exec(t_cmd_params *cmd, char *command)
{
	t_list		**envp;
	t_main_envp	*imp;
	int			res;

	imp = cmd->imp;
	envp = cmd->envp;
	free_cmd(cmd, 1);
	free(cmd);
	imp->is_bquoted++;
	execute_line(command, envp, imp);
	res = imp->exit_status;
	free_envp(envp, imp);
	exit(res);
}

static void	execute_pipe_cmd(t_cmd_params *cmd, int pipes[2], int last)
{
	int		res;
	char	*command;

	command = ft_strdup((char *)cmd->pipes->content);
	close(pipes[last]);
	if (!command[0])
	{
		free(command);
		close(pipes[!last]);
		res = cmd->imp->exit_status;
		free_cmd(cmd, 1);
		free(cmd);
		exit(res);
	}
	cmd->imp->input_fd = ((pipes[0] * last) + (cmd->imp->input_fd * !last));
	cmd->imp->output_fd = ((cmd->imp->output_fd * last) + (pipes[1] * !last));
	handle_pipe_exec(cmd, command);
}

int	execute_pipes(t_cmd_params *cmd)
{
	t_int_tab	itab;
	int			pipes[2];
	pid_t		pid;

	itab = init_int_tab();
	itab.res = ft_lstsize(cmd->pipes);
	while (++itab.i < itab.res)
	{
		if ((itab.i + 1) != itab.res)
			if (pipe(pipes) < 0)
				return (1);
		pid = fork();
		if (pid < 0)
			return (1);
		if (!pid)
			execute_pipe_cmd(cmd, pipes, (itab.i + 1) == itab.res);
		go_to_next_command(&cmd->pipes, &(cmd->imp->input_fd), pipes);
	}
	return (wait_line_end_exec(itab.res, pipes[0], cmd, pid));
}
