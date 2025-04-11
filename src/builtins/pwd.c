/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:09:54 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/12 01:04:28 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(t_cmd_params *cmd)
{
	char	*cwd;

	cwd = cmd->imp->cwd;
	if (!cwd)
	{
		cwd_error("pwd: ");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
