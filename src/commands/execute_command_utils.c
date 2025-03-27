/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:22:50 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 00:37:46 by gakarbou         ###   ########.fr       */
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

t_cmd_params	*make_cmd(void *argv_ptr, t_list **envp, t_main_envp *imp)
{
	t_cmd_params	*dest;

	dest = malloc(sizeof(t_cmd_params));
	if (!dest)
		return (NULL);
	dest->argv = (char **)argv_ptr;
	dest->redir = NULL;
	dest->envp = envp;
	dest->imp = imp;
	return (dest);
}
