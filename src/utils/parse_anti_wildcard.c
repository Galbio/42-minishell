/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_anti_wildcard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:08:05 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/14 09:11:47 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_parsed_size(char *str)
{
	int		res;
	int		i;

	res = 0;
	i = -1;
	while (str[++i])
	{
		if (ft_strchr("*[?", str[i]))
			res++;
	}
	return (i + res);
}

char	*parse_anti_wildcard(char *str)
{
	char	*dest;
	int		size;
	int		i;

	size = get_parsed_size(str);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (str);
	size = 0;
	i = -1;
	while (str[++i])
	{
		if (ft_strchr("*[?", str[i]))
			dest[size++] = '\\';
		dest[size++] = str[i];
	}
	dest[size] = 0;
	free(str);
	return (dest);
}
