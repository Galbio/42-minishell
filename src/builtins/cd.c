/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:19:55 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/12 15:07:52 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cd(t_cmd_params *cmd)
{
	int	res;

	if (!cmd->argv[1])
	{
		if (getenv("HOME"))
			chdir(getenv("HOME"));
		else
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return ;
	}
	else if (cmd->argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return ;
	}
	res = chdir(cmd->argv[1]);
	if (res < 0)
		ft_putstr_fd(strerror(errno), 2);
}
