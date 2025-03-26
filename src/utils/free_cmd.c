/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:17:38 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/26 21:13:50 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(t_list **envp, t_main_envp *imp, char is_bin)
{
	int		i;

	ft_lstclear(envp, free);
	i = -1;
	if (!is_bin)
	{
		while (imp->envp_cpy[++i])
			free(imp->envp_cpy[++i]);
		free(imp->envp_cpy);
	}
	i = -1;
	while (imp->path[++i])
		free(imp->path[++i]);
	free(imp->path);
	free(imp->home);
}

void	free_cmd(t_cmd_params *cmd, char mode)
{
	int		i;

	if (mode != 'b')
	{
		i = -1;
		while (cmd->argv[++i])
			free(cmd->argv[i]);
		free(cmd->argv);
	}
	i = -1;
	free_envp(cmd->envp, cmd->imp, mode == 'b');
	ft_lstclear(&cmd->redir, free);
	free(cmd);
	free_readline(0);
}
