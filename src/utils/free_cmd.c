/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:17:38 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/14 06:55:27 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "regex.h"

char	free_redir(t_list *cur, char res)
{
	t_list			*temp;
	t_redirection	*redir;
	int				i;

	i = 0;
	while (cur)
	{
		redir = cur->content;
		i = -1;
		while (redir->values[++i])
			free(redir->values[i]);
		free(redir->values);
		free(redir->method);
		free(redir->og_str);
		free(redir);
		temp = cur;
		cur = cur->next;
		free(temp);
	}
	return (res);
}

void	free_envp(t_list **envp, t_main_envp *imp)
{
	int		i;

	ft_lstclear(envp, free);
	if (get_depth(0))
	{
		free_readline();
		free_regex_items();
	}
	i = -1;
	while (imp->path && imp->path[++i])
		free(imp->path[i]);
	ft_lstclear(&imp->aliases, free);
	ft_lstclear(&imp->cmd_queue, free);
	free(imp->path);
	free(imp->home);
	free(imp->user);
	free(imp->cwd);
	free(imp->current_home);
	free(imp->env_pwd);
}

void	free_cmd(t_cmd_params *cmd, char mode)
{
	int		i;

	ft_lstclear(&cmd->pipes, free);
	if ((mode != 'b') && (mode != 's'))
	{
		i = -1;
		while (cmd->argv && cmd->argv[++i])
			free(cmd->argv[i]);
		free(cmd->argv);
	}
	if ((mode != 'c') && (mode != 's'))
	{
		ft_lstclear(&cmd->cmds, free);
		ft_lstclear(&cmd->sep, free);
	}
}
