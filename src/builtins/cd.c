/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:19:55 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/23 21:33:25 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cd(char *name)
{
	int	res;
	int	i;

	i = -1;
	while (name[++i])
		if (name[i] == 32)
			break ;
	if (!name[i])
	{
		if (getenv("HOME"))
			chdir(getenv("HOME"));
		else
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	name += 3;
	res = chdir(name);
	if (res < 0)
		ft_putstr_fd(strerror(errno), 2);
	free(name - 3);
	return (NULL);
}
