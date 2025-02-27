/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 03:46:01 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/27 20:52:05 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_var_commands(char *command, t_list **envp, t_main_envp *imp)
{
	char	*str;

	command[ft_strlen(command) - 1] = 0;
	str = execute_command(command, envp, imp);
	return (str);
}

char	*parse_var(char *var_name, t_list **envp, t_main_envp *imp)
{
	t_list	*cur;
	char	*cur_env;
	int		len;

	if (var_name[0] == '(')
		return (handle_var_commands(var_name + 1, envp, imp));
	len = ft_strlen(var_name);
	cur = *envp;
	while (cur)
	{
		cur_env = (char *)cur->content;
		if ((cur_env[len] == '=') && (!ft_strncmp(cur_env, var_name, len)))
			return (ft_strdup(cur_env + len + 1));
		cur = cur->next;
	}
	return (NULL);
}
