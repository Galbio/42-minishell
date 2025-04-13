/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:23:12 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/12 22:28:53 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_path_count(char *str)
{
	int		res;
	int		i;

	res = 0;
	i = -1;
	while (str[++i])
		if ((str[i] == ':') && (str[i - 1] != '\\'))
			res++;
	return (res + 1);
}

static char	*create_pathname(char **str)
{
	char	*dest;
	int		size;
	int		i;

	i = -1;
	size = 0;
	while (str[0][++size])
		if ((str[0][size] == ':') && (str[0][size - 1] != '\\'))
			break ;
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = 0;
	i = -1;
	while (++i < size)
		dest[i] = str[0][i];
	*str += size + 1;
	return (dest);
}

char	**parse_path(char *str)
{
	char	**dest;
	int		size;

	size = get_path_count(str);
	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = 0;
	while (--size >= 0)
		dest[size] = create_pathname(&str);
	return (dest);
}
