/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 01:58:15 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/13 01:59:33 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(t_list **envp, t_main_envp *imp)
{
	int		i;

	ft_lstclear(envp, free);
	i = -1;
	while (imp->path[++i])
		free(imp->path[i]);
	i = -1;
	while (imp->envp_cpy[++i])
		free(imp->envp_cpy[i]);
	free(imp->envp_cpy);
	free(imp->path);
	free(imp->home);
}
