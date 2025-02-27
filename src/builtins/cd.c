/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:19:55 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/27 18:49:37 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_cd(char **argv)
{
	int	res;

	if (!argv[1])
	{
		if (getenv("HOME"))
			chdir(getenv("HOME"));
		else
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	else if (argv[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), NULL);
	res = chdir(argv[1]);
	if (res < 0)
		ft_putstr_fd(strerror(errno), 2);
	return (NULL);
}
