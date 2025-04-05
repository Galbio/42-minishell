/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 06:06:08 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/03 15:03:34 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

int	square_brackets_parse(char *value, t_array *array)
{
	int		count;
	int		i;
	int		j;
	char	*parsed;

	count = 2 + 1 * (value[1] && value[1] == '-'
			&& value[2] && value[2] != ']');
	parsed = malloc(sizeof(char) * count);
	if (!parsed)
		return (0);
	i = 0;
	j = 0;
	while (i < (count - 1))
	{
		j += ((j == 1) && (value[j] == '-'));
		parsed[i] = value[j];
		i++;
		j++;
	}
	parsed[i] = '\0';
	ft_array_push(array, parsed);
	return (j);
}

static int	square_brackets_test(char c, char *value)
{
	if (ft_strlen(value) == 2)
		return (c >= ft_min(value[0], value[1])
			&& c <= ft_max(value[0], value[1]));
	return (c == value[0]);
}

int	square_brackets_match(char *value, t_array parsed)
{
	int	i;
	int	size;

	i = 0;
	size = ft_array_count(parsed);
	while (i < size)
	{
		if (square_brackets_test(value[0], ((char **)parsed)[i]))
			return (1);
		i++;
	}
	return (0);
}

int	square_brackets_neg_match(char *value, t_array parsed)
{
	int	i;
	int	size;

	i = 0;
	size = ft_array_count(parsed);
	while (i < size)
	{
		if (square_brackets_test(value[0], ((char **)parsed)[i]))
			return (0);
		i++;
	}
	return (1);
}
