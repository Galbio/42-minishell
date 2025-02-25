/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:55:20 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/24 23:33:18 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_builtins(int code, char *cmd, t_list **envp, t_main_envp *imp)
{
	if (code == 1)
		return (ft_echo(cmd));
	else if (code == 2)
		return (ft_cd(cmd));
	else if (code == 3)
		return (ft_pwd());
	else if (code == 4)
		return (ft_export(cmd, envp));
	else if (code == 5)
		return (ft_unset(cmd, envp, imp));
	else if (code == 7)
		return (ft_exit(cmd));
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
		return (handle_builtins(tabe.res, command, &envp, imp));
	dest = execute_command(command, envp, imp);
	return (free(command), dest);
}
