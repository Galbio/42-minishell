/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 03:46:01 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/23 11:04:00 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_command(char *command, t_list *envp, t_main_envp *imp)
{
	int		len;

	len = ft_strlen(command);
	command[len - 1] = 0;
	return (execute_command(command, envp, imp));
}

char	*parse_var(char *var_name, t_list *envp, t_main_envp *imp)
{
	char	*cur_env;
	int		len;

	if (var_name[0] == '(')
		return (parse_command(var_name + 1, envp, imp));
	len = ft_strlen(var_name);
	while (envp)
	{
		cur_env = (char *)envp->content;
		if ((cur_env[len] == '=') && (!ft_strncmp(cur_env, var_name, len)))
			return (ft_strdup(cur_env + len + 1));
		envp = envp->next;
	}
	return (NULL);
}
