/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:34:13 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/08 01:14:38 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_is_imp(char *name, t_main_envp *imp)
{
	int		i;

	if (ft_strncmp(name, "SHLVL", 6) == 0)
		imp->shell_level = 0;
	else if (ft_strncmp(name, "HOME", 5) == 0)
	{
		free(imp->home);
		imp->home = NULL;
	}
	else if (ft_strncmp(name, "PATH", 5) == 0)
	{
		i = -1;
		while (imp->path[++i])
			free(imp->path[i]);
		free(imp->path[i]);
		imp->path = NULL;
	}
}

static void	delete_env(int i, t_list **envp)
{
	t_list	*cur;
	t_list	*temp;

	cur = *envp;
	if (!i)
	{
		temp = cur->next;
		ft_lstdelone(cur, free);
		*envp = temp;
		return ;
	}
	while (i-- != 1)
		cur = cur->next;
	temp = cur->next->next;
	ft_lstdelone(cur->next, free);
	cur->next = temp;
}

void	unset_var(char *name, t_list **envp, t_main_envp *imp)
{
	t_list	*cur;
	char	*env;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name);
	cur = *envp;
	while (cur)
	{
		env = (char *)cur->content;
		env += (env[0] == '\\');
		if ((!ft_strncmp(env, name, len)) && (env[len] == '='))
		{
			delete_env(i, envp);
			check_is_imp(name, imp);
			return ;
		}
		cur = cur->next;
		i++;
	}
}

int	ms_unset(t_cmd_params *cmd)
{
	int		i;

	if (!cmd->argv[1])
		return (0);
	i = 0;
	while (cmd->argv[++i])
		unset_var(cmd->argv[i], cmd->envp, cmd->imp);
	return (0);
}
