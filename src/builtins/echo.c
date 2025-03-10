/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:14:37 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/27 18:49:42 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	handle_n(char *str, char *nl)
{
	int		i;

	if (!str[0] || (str[0] != '-'))
		return (0);
	i = 0;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	*nl = 0;
	return (1);
}

char	*ms_echo(char **argv)
{
	char	*str;
	char	nl;
	int		i;

	i = 0;
	nl = 1;
	str = ft_strdup("");
	while (argv[++i])
		if (!handle_n(argv[i], &nl))
			break ;
	i--;
	while (argv[++i])
	{
		str = ft_securejoin(str, argv[i], 1);
		if (argv[i + 1])
			str = ft_securejoin(str, " ", 1);
	}
	if (nl)
		str = ft_securejoin(str, "\n", 1);
	return (str);
}
