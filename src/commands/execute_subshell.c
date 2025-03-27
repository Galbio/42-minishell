/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 01:57:21 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 02:08:10 by gakarbou         ###   ########.fr       */
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
	execute_line(get_subshell(command), envp, imp);
	stat = imp->exit_status;
	free_envp(envp, imp, 0);
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
