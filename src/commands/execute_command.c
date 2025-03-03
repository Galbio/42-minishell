/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:04:40 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/03 15:36:02 by gakarbou         ###   ########.fr       */
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
	t_int_tab	tabe;
	char		**argv;

	tabe = init_int_tab();
	argv = create_command_argv(str, envp, imp);
	tabe.ret = check_builtins(argv[0]);
	if (tabe.ret)
		tabe.ptr1 = handle_builtins(tabe.ret, argv, envp, imp);
	else
		tabe.ptr1 = execute_bin(argv, imp);
	while (argv[++tabe.i])
		free(argv[tabe.i]);
	free(argv);
	if (imp->is_bquoted)
		tabe.ptr1 = clean_whitespaces(tabe.ptr1);
	return (tabe.ptr1);
}
