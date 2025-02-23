/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:55:20 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/23 21:33:17 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_builtins(int code, char *command)
{
	if (code == 1)
		return (ft_echo(command));
	else if (code == 3)
		return (ft_pwd());
	else if (code == 2)
		return (ft_cd(command));
	return (NULL);
}

char	*parse_commands(char *str, t_list *envp, t_main_envp *imp)
{
	t_int_tab	tabe;
	char		*command;
	char		*dest;

	tabe = init_int_tab();
	command = parse_quotes(str, envp, imp);
	tabe.res = check_built_in(&command);
	if (tabe.res)
		return (handle_builtins(tabe.res, command));
	dest = execute_command(command, envp, imp);
	return (free(command), dest);
}
