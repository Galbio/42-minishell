/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 01:57:21 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/07 14:59:30 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_subshell(t_cmd_params *cmd)
{
	char		*command;
	int			stat;
	t_list		**envp;
	t_main_envp	*imp;

	envp = cmd->envp;
	imp = cmd->imp;
	command = ft_strdup(cmd->argv[0]);
	free_cmd(cmd, 'b');
	free(cmd);
	imp->is_bquoted++;
	execute_line(get_subcmd(command), envp, imp);
	stat = imp->exit_status;
	free_envp(envp, imp);
	exit(stat);
}

int	execute_subshell(t_cmd_params *cmd)
{
	pid_t	pid;
	int		stat;
	int		res;

	res = cmd->imp->exit_status;
	pid = fork();
	if (pid < 0)
		return (-1);
	if (!pid)
		handle_subshell(cmd);
	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		res = WEXITSTATUS(stat);
	free_cmd(cmd, 's');
	free(cmd);
	return (res);
}
