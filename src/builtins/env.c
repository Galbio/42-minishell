/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:11:56 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/27 18:49:51 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	check_error(char **argv)
{
	int		i;

	i = 0;
	while (argv[++i])
	{
		if (!ft_strchr(argv[i], '='))
		{
			ft_putstr_fd("env: ‘", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("’: No such file or directory", 2);
			return (1);
		}
	}
	return (0);
}

char	*ms_env(char **argv, t_list *envp)
{
	char	*dest;
	int		i;

	if (argv[1] && check_error(argv))
		return (ft_strdup("\n"));
	dest = NULL;
	while (envp)
	{
		dest = ft_securejoin(dest, (char *)envp->content, 1);
		dest = ft_securejoin(dest, "\n", 1);
		envp = envp->next;
	}
	i = 0;
	while (argv[++i])
	{
		dest = ft_securejoin(dest, argv[i], 1);
		dest = ft_securejoin(dest, "\n", 1);
	}
	return (dest);
}
