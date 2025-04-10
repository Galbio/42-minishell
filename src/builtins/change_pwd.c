/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:55:36 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/10 15:28:41 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_pwd_nodes(t_list **envp, t_list **old_pwd, t_list **pwd)
{
	t_list	*cur;

	*old_pwd = NULL;
	*pwd = NULL;
	cur = *envp;
	while (cur)
	{
		if (!ft_strncmp("PWD=", (char *)cur->content, 4))
			*pwd = cur;
		else if (!ft_strncmp("OLDPWD=", (char *)cur->content, 7))
			*old_pwd = cur;
		if (*old_pwd && *pwd)
			return ;
		cur = cur->next;
	}
}

static int	update_pwd(t_main_envp *imp, char **new_path, char **arg)
{
	if ((*new_path) == NULL)
	{
		if (!imp->pwd)
		{
			printf("chdir: error retrieving current directory: getcwd: cannot");
			printf(" access parent directories: No such file or directory\n");
			if (ft_iscurrent_dirpath(*arg))
				*new_path = ft_strdup(".");
			else
				*new_path = ft_cleanpath(*arg);
		}
		else if (ft_iscurrent_dirpath(*arg))
			return (0);
		else if (imp->pwd[0] == '.' && !imp->pwd[1])
			*new_path = ft_cleanpath(*arg);
		else
		{
			*arg = ft_cleanpath(*arg);
			*new_path = ft_pathjoin(imp->pwd, *arg);
			free(*arg);
		}
	}
	free(imp->pwd);
	imp->pwd = ft_strdup(*new_path);
	return (1);
}

void	change_envp_pwd(t_list **envp, t_main_envp *imp,
	char *new_path, char *arg)
{
	t_list	*pwd;
	t_list	*old_pwd;
	void	*temp;

	if (!update_pwd(imp, &new_path, &arg))
		return ;
	get_pwd_nodes(envp, &old_pwd, &pwd);
	temp = NULL;
	if (pwd)
	{
		temp = pwd->content;
		if (old_pwd)
		{
			free(old_pwd->content);
			old_pwd->content = ft_strjoin("OLD", pwd->content);
		}
		else
			ft_lstadd_back(envp, ft_lstnew(
					ft_strjoin("OLD", pwd->content)));
		pwd->content = ft_strjoin("PWD=", new_path);
		free(temp);
	}
	else
		ft_lstadd_back(envp, ft_lstnew(ft_strjoin("PWD=", new_path)));
	free(new_path);
}
