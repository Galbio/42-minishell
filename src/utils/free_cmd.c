/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:17:38 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/04 10:42:25 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "regex.h"

char	free_redir(t_list *cur, char res)
{
	t_list	*temp;
	int		i;

	i = 0;
	while (cur)
	{
		temp = cur;
		cur = cur->next;
		if (i % 2)
			free(((char **)(temp->content))[1]);
		free(temp->content);
		free(temp);
		i++;
	}
	return (res);
}

void	free_envp(t_list **envp, t_main_envp *imp)
{
	int		i;

	ft_lstclear(envp, free);
	if (imp->is_bquoted)
	{
		free_readline_main();
		free_regex_items();
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
