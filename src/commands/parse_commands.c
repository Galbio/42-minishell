/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:55:20 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/10 16:33:57 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pwd(void)
{
	t_int_tab	itab;
	char		**argv;
	char		*dest;

	itab = init_int_tab();
	argv = create_command_argv(str, envp, imp);
	itab.ret = check_built_in(&argv[0]);
	if (itab.ret)
		dest = handle_builtins(itab.ret, argv, &envp, imp);
	else
		dest = execute_command(argv, imp);
	while (argv[++itab.i])
		free(argv[itab.i]);
	return (free(argv), dest);
}
