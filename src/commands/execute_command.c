/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:04:40 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/05 13:28:08 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_builtins(int code, char **argv, t_list **envp
		, t_main_envp *imp)
{
	if (code == 1)
		return (ms_echo(argv));
	else if (code == 2)
		return (ms_cd(argv));
	else if (code == 3)
		return (ms_pwd());
	else if (code == 4)
		return (ms_export(argv, envp));
	else if (code == 5)
		return (ms_unset(argv, envp, imp));
	else if (code == 6)
		return (ms_env(argv, *envp));
	else if (code == 7)
		return (ms_exit(argv));
	return (NULL);
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

char	*execute_command(char *str, t_list **envp, t_main_envp *imp)
{
	t_int_tab	itab;
	char		**argv;

	itab = init_int_tab();
	argv = create_command_argv(str, envp, imp);
	itab.ret = check_builtins(argv[0]);
	if (itab.ret)
		itab.ptr1 = handle_builtins(itab.ret, argv, envp, imp);
	else
		itab.ptr1 = execute_bin(argv, imp);
	while (argv[++itab.i])
		free(argv[itab.i]);
	free(argv);
	if (imp->is_bquoted)
		itab.ptr1 = clean_whitespaces(itab.ptr1);
	return (itab.ptr1);
}
