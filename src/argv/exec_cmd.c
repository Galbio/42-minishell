/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:23:34 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 16:24:03 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_sub_cmd(t_int_tab *itab, t_cmd_params *cmd,
		int pipes[2], t_list **outputs)
{
	int			res;
	t_list		**envp;
	t_main_envp	*imp;

	ft_lstclear(outputs, free);
	ft_lstclear(cmd->extra, free);
	cmd->extra = NULL;
	free(itab->ptr2);
	imp = cmd->imp;
	envp = cmd->envp;
	close(pipes[0]);
	free_cmd(cmd, 1);
	free(cmd);
	imp->output_fd = pipes[1];
	imp->is_bquoted++;
	execute_line(itab->ptr1, envp, imp);
	res = imp->exit_status;
	free_envp(envp, imp);
	exit(res);
}

char	*handle_commands(t_int_tab *itab, t_cmd_params *cmd,
		t_list **outputs)
{
	pid_t	pid;
	int		pipes[2];
	int		stat;
	char	*dest;

	if (pipe(pipes) < 0)
		return (NULL);
	pid = fork();
	if (!pid)
		execute_sub_cmd(itab, cmd, pipes, outputs);
	close(pipes[1]);
	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		cmd->imp->exit_status = WEXITSTATUS(stat);
	dest = ft_get_contents(pipes[0]);
	close(pipes[0]);
	return (parse_var_return(dest, itab->cur_quote));
}
