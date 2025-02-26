/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:55:20 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/26 00:37:52 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_builtins(int code, char **argv, t_list **envp, t_main_envp *imp)
{
	(void)envp;
	(void)imp;
	if (code == 1)
		return (ft_echo(argv));
	/*
	else if (code == 2)
		return (ft_cd(argv));*/
	else if (code == 3)
		return (ft_pwd());
	/*else if (code == 4)
		return (ft_export(argv, envp));
	else if (code == 5)
		return (ft_unset(argv, envp, imp));
		*/
	else if (code == 7)
		return (ft_exit(argv));
	return (NULL);
}

char	*parse_commands(char *str, t_list *envp, t_main_envp *imp)
{
	t_int_tab	tabe;
	char		**argv;
	char		*dest;

	tabe = init_int_tab();
	argv = create_command_argv(str, envp, imp);
	tabe.res = check_built_in(&argv[0]);
	if (tabe.res)
		dest = handle_builtins(tabe.res, argv, &envp, imp);
	else
		dest = execute_command(argv, imp);
	while (argv[++tabe.i])
		free(argv[tabe.i]);
	return (free(argv), dest);
}
