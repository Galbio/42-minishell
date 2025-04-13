/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:55:36 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/13 01:27:08 by lroussel         ###   ########.fr       */
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
		if (!imp->cwd)
		{
			cwd_error("chdir: ");
			if (ft_iscurrent_dirpath(*arg))
				*new_path = ft_strdup(".");
			else
				*new_path = ft_cleanpath(*arg);
		}
		else if (ft_iscurrent_dirpath(*arg))
			return (0);
		else if (imp->cwd[0] == '.' && !imp->cwd[1])
			*new_path = ft_cleanpath(*arg);
		else
		{
			*arg = ft_cleanpath(*arg);
			*new_path = ft_pathjoin(imp->cwd, *arg);
			free(*arg);
		}
	}
	free(imp->cwd);
	imp->cwd = ft_strdup(*new_path);
	return (1);
}

static void	change_when_isset(t_cmd_params *cmd, t_list *pwd, t_list *old_pwd,
	char *new_path)
{
	void	*temp;

	temp = pwd->content;
	if (old_pwd)
	{
		free(old_pwd->content);
		old_pwd->content = ft_strjoin("OLD", pwd->content);
	}
	else
		ft_lstadd_back(cmd->envp, ft_lstnew(
				ft_strjoin("OLD", pwd->content)));
	pwd->content = ft_strjoin("PWD=", new_path);
	free(temp);
}

void	change_envp_pwd(t_cmd_params *cmd, char *new_path)
{
	t_list	*pwd;
	t_list	*old_pwd;
	char	*arg;
	char	*joined;

	arg = cmd->argv[1];
	if (!update_pwd(cmd->imp, &new_path, &arg))
		return ;
	get_pwd_nodes(cmd->envp, &old_pwd, &pwd);
	joined = ft_strjoin("PWD=", new_path);
	update_imp_values(joined, cmd->imp);
	if (pwd)
	{
		change_when_isset(cmd, pwd, old_pwd, new_path);
		free(joined);
	}
	else
		ft_lstadd_back(cmd->envp, ft_lstnew(joined));
	free(new_path);
}
