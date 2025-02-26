/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:19:55 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/26 19:32:48 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cd(char **argv)
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
