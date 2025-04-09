/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:09:54 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/10 00:34:58 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(t_cmd_params *cmd)
{
	char	*pwd;

	pwd = cmd->imp->pwd;
	if (!pwd)
	{
		printf("pwd: error retrieving current directory: getcwd: cannot");
		printf(" access parent directories: No such file or directory\n");
		return (1);
	}
	printf("%s\n", pwd);
	return (0);
}
