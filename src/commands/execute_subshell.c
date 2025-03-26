/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 01:57:21 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/26 20:23:35 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_subshell(char *str)
{
	t_int_tab	itab;

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
			return (ft_substr(str, 1, itab.i - 1));
	}
	return (ft_substr(str, 1, itab.i - 1));
}

int	execute_subshell(char *command, t_list **envp, t_main_envp *imp)
{
	pid_t	pid;
	int		stat;

	pid = fork();
	if (pid < 0)
		return (-1);
	imp->is_bquoted++;
	if (!pid)
	{
		execute_line(get_subshell(command), envp, imp);
		exit(imp->exit_status);
	}
	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		imp->exit_status = WEXITSTATUS(stat);
	imp->is_bquoted--;
	return (imp->exit_status);
}
