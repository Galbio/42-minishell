/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:22:50 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/14 19:45:35 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_builtins(int code, t_cmd_params *cmd)
{
	if (code == 1)
		return (ms_echo(cmd));
	else if (code == 2)
		return (ms_cd(cmd));
	else if (code == 3)
		return (ms_pwd());
	else if (code == 4)
		return (ms_export(cmd));
	else if (code == 5)
		return (ms_unset(cmd));
	else if (code == 6)
		return (ms_env(cmd));
	else if (code == 7)
		return (ms_exit(cmd));
	return (0);
}

char	check_builtins(char *name)
{
	char		*temp;

	temp = ft_strrchr(name, '/');
	if (temp)
		name = temp + 1;
	if (ft_strncmp(name, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(name, "cd", 3) == 0)
		return (2);
	else if (ft_strncmp(name, "pwd", 4) == 0)
		return (3);
	else if (ft_strncmp(name, "export", 7) == 0)
		return (4);
	else if (ft_strncmp(name, "unset", 6) == 0)
		return (5);
	else if (ft_strncmp(name, "env", 4) == 0)
		return (6);
	else if (ft_strncmp(name, "exit", 5) == 0)
		return (7);
	return (0);
}

void	go_to_next_command(t_list **commands, int *temp, int pipes[2])
{
	*commands = (*commands)->next;
	if (*temp)
		close(*temp);
	*temp = pipes[0];
	close(pipes[1]);
}

int	wait_line_end_exec(int nb_cmd, int write_pipe, int read_pipe, pid_t pid)
{
	int		i;
	int		stat;
	int		res;
	int		ret;

	if (write_pipe)
		close(write_pipe);
	close(read_pipe);
	i = -1;
	ret = 0;
	while (++i < nb_cmd)
	{
		res = wait(&stat);
		if (res == pid)
			if (WIFEXITED(stat))
				ret = WEXITSTATUS(stat);
	}
	return (ret);
}

t_cmd_params	make_cmd(void *argv_ptr, t_list **envp, t_main_envp *imp)
{
	t_cmd_params	dest;

	dest.argv = (char **)argv_ptr;
	dest.envp = envp;
	dest.imp = imp;
	return (dest);
}
