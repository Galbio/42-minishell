/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 01:57:21 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 01:05:26 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_subshell(char *str)
{
	t_int_tab	itab;
	char		*dest;

	itab = init_int_tab();
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(str, &itab);
		if (!itab.backslash && !itab.cur_quote && (str[itab.i] == '$'))
			itab.i += go_to_var_end(str + itab.i) - 1;
		else if (!itab.backslash && !itab.cur_quote && (str[itab.i] == '('))
			itab.ret++;
		else if (!itab.backslash && !itab.cur_quote && (str[itab.i] == ')'))
			itab.ret--;
		if (!itab.ret)
		{
			dest = ft_substr(str, 1, itab.i - 1);
			free(str);
			return (dest);
		}
	}
	dest = ft_substr(str, 1, itab.i - 1);
	free(str);
	return (dest);
}

int	execute_subshell(t_cmd_params *cmd)
{
	pid_t	pid;
	int		stat;
	char	*command;

	pid = fork();
	if (pid < 0)
		return (-1);
	cmd->imp->is_bquoted++;
	if (!pid)
	{
		command = ft_strdup(cmd->argv[0]);
		free(cmd->argv[0]);
		free_cmd(cmd, 's');
		execute_line(get_subshell(command), cmd->envp, cmd->imp);
		stat = cmd->imp->exit_status;
		free_readline_core();
		free_envp(cmd->envp, cmd->imp, 0);
		free(cmd);
		exit(stat);
	}
	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		cmd->imp->exit_status = WEXITSTATUS(stat);
	cmd->imp->is_bquoted--;
	return (cmd->imp->exit_status);
}
