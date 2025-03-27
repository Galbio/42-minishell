/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:55:36 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 14:10:33 by gakarbou         ###   ########.fr       */
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

void	change_envp_pwd(t_list **envp, char *new)
{
	t_list	*pwd;
	t_list	*old_pwd;
	void	*temp;

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
		pwd->content = ft_strjoin("PWD=", new);
		free(temp);
	}
	else
		ft_lstadd_back(envp, ft_lstnew(ft_strjoin("PWD=", new)));
	free(new);
}
