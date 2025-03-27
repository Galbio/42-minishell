/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:17:38 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 02:14:44 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(t_list **envp, t_main_envp *imp, char is_bin)
{
	int		i;

	ft_lstclear(envp, free);
	if (imp->is_bquoted)
		free_readline_core();
	i = -1;
	if (!is_bin)
	{
		while (imp->envp_cpy && imp->envp_cpy[++i])
			free(imp->envp_cpy[i]);
		free(imp->envp_cpy);
	}
	i = -1;
	while (imp->path && imp->path[++i])
		free(imp->path[i]);
	free(imp->path);
	free(imp->home);
}

void	free_cmd(t_cmd_params *cmd, char mode)
{
	int		i;

	if ((mode != 'b') && (mode != 's'))
	{
		i = -1;
		while (cmd->argv && cmd->argv[++i])
			free(cmd->argv[i]);
		free(cmd->argv);
	}
	ft_lstclear(&cmd->pipes, free);
	if ((mode != 'c') && (mode != 's'))
	{
		ft_lstclear(&cmd->cmds, free);
		ft_lstclear(&cmd->sep, free);
	}
	if (cmd->redir)
		ft_lstclear(&cmd->redir, free);
}
