/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:55:20 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/25 17:41:00 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_commands(char *str, t_list *envp, t_main_envp *imp)
{
	t_int_tab	tabe;
	char		**argv;
	char		*dest;

	tabe = init_int_tab();
	argv = create_command_argv(str, envp, imp);
	tabe.res = check_built_in(&argv[0]);
	dest = execute_command(argv, imp);
	while (argv[++tabe.i])
		free(argv[tabe.i]);
	return (free(argv), dest);
}
