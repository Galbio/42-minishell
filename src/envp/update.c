/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 01:19:41 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/13 01:28:17 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_imp_values(char *name, t_main_envp *imp)
{
	if (ft_strncmp(name, "HOME=", 5) == 0)
	{
		free(imp->current_home);
		if (!name[5])
			imp->current_home = ft_strdup("");
		else
			imp->current_home = ft_strdup(name + 5);
	}
	if (ft_strncmp(name, "PWD=", 4) == 0)
	{
		free(imp->env_pwd);
		if (!name[4])
			imp->env_pwd = ft_strdup("");
		else
			imp->env_pwd = ft_strdup(name + 4);
	}
}
