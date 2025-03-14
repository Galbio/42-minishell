/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:19:55 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/13 23:02:55 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd(t_cmd_params *cmd)
{
	int	res;

	if (!cmd->argv[1])
	{
		res = getenv("HOME") != NULL;
		if (res)
			chdir(getenv("HOME"));
		else
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (res);
	}
	else if (cmd->argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	res = chdir(cmd->argv[1]);
	if (res < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}
