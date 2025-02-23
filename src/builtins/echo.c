/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:14:37 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/23 18:01:43 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_n(char **str, int *i, char *nl)
{
	while (str[0][*i])
	{
		if (str[0][*i] != '-')
			return ;
		if (!str[0][(*i) + 1])
			return ;
		*i += 1;
		while (str[0][*i] && (str[0][*i] != 32))
			if (str[0][(*i)++] != 'n')
				return ;
		*nl = 0;
		if (str[0][*i] == 32)
			*i += 1;
	}
}

char	*ft_echo(char *command)
{
	char	*str;
	char	*temp;
	char	nl;
	int		i;

	i = -1;
	str = command;
	while (str[++i])
		if (str[i] == 32)
			break ;
	if (!str[i])
		return (ft_strdup("\n"));
	nl = 1;
	i++;
	handle_n(&str, &i, &nl);
	str += i;
	temp = ft_strdup(str);
	if (nl)
		temp = ft_securejoin(temp, "\n", 1);
	free(str - i);
	return (temp);
}
