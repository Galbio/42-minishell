/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 03:46:01 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/25 17:42:13 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_command(char *command, t_list *envp, t_main_envp *imp)
{
	char	**argv;
	char	*str;
	int		len;

	len = ft_strlen(command);
	command[len - 1] = 0;
	argv = create_command_argv(command, envp, imp);
	str = execute_command(argv, imp);
	len = -1;
	while (argv[++len])
		free(argv[len]);
	free(argv);
	return (str);
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
