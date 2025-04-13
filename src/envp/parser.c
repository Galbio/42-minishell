/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:57:32 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/14 00:02:22 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_value(char *str, char *value, int len, int *already_set)
{
	if (*already_set || ft_strncmp(value, str, len) != 0)
		return (0);
	*already_set = 1;
	return (1);
}

void	handle_important(char *str, t_main_envp *imp)
{
	static int	important[5] = {0, 0, 0, 0, 0};

	if (check_value(str, "SHLVL=", 6, &important[0]))
		imp->shell_level = ft_atoi(str + 6);
	else if (check_value(str, "HOME=", 5, &important[1]))
	{
		imp->home = ft_strdup(str + 5);
		imp->current_home = ft_strdup(str + 5);
	}
	else if (check_value(str, "PATH=", 5, &important[2]))
		imp->path = parse_path(str + 5);
	else if (check_value(str, "PWD=", 4, &important[3]) && str[4])
	{
		if (!imp->cwd)
			imp->cwd = ft_strdup(str + 4);
		imp->env_pwd = ft_strdup(str + 4);
	}
	else if (check_value(str, "USER=", 5, &important[4]))
		imp->user = ft_strdup(str + 5);
}

static void	init_imp(t_main_envp *imp)
{
	imp->aliases = NULL;
	imp->path = NULL;
	imp->home = NULL;
	imp->user = NULL;
	imp->cwd = getcwd(NULL, 0);
	imp->current_home = NULL;
	imp->env_pwd = NULL;
	imp->cmd_queue = NULL;
	imp->shell_level = 0;
	imp->cmd_count = 0;
}

t_list	*parse_envp(char **envp, t_main_envp *imp)
{
	t_list	*dest;
	void	*temp;
	int		i;

	init_imp(imp);
	if (!envp || !envp[0])
		return (NULL);
	dest = NULL;
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "SHLVL=", 6))
		{
			temp = ft_itoa(ft_atoi(envp[i] + 6) + 1);
			ft_lstadd_back(&dest, ft_lstnew(ft_strjoin("SHLVL=", temp)));
			free(temp);
		}
		else
			ft_lstadd_back(&dest, ft_lstnew(ft_strdup(envp[i])));
		handle_important(envp[i], imp);
	}
	return (dest);
}
