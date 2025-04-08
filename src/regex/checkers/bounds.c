/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:21:29 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/03 16:21:29 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

static void	resize_value(char **value, int start, int end)
{
	char	*new;

	new = ft_substr(*value, start, end);
	free(*value);
	*value = new;
}

int	check_beginning(char **text, char **pattern)
{
	int				i;
	int				j;
	t_regex_item	*item;

	i = 0;
	j = 0;
	while ((*pattern)[i] && (*pattern)[i] != '*')
	{
		item = get_regex_item((*pattern) + i);
		if (item)
		{
			if (!regex_item_match((*text) + j, item->last_finded, item))
				return (0);
			i += ft_strlen(item->last_finded) - 1;
		}
		else if ((*pattern)[i] != '?' && (*pattern)[i] != (*text)[j])
			return (0);
		i++;
		j++;
	}
	resize_value(pattern, i, ft_strlen(*pattern) - i);
	resize_value(text, j, ft_strlen(*text) - j);
	return (1);
}

int	check_end(char **text, char **pattern)
{
	int				i;
	int				j;
	t_regex_item	*item;

	i = ft_strlen(*pattern) - 1;
	j = ft_strlen(*text) - 1;
	while (i >= 0 && (*pattern)[i] != '*')
	{
		item = get_regex_item_from_end((*pattern), i);
		if (item)
		{
			if (!regex_item_match((*text) + j, item->last_finded, item))
				return (0);
			i -= ft_strlen(item->last_finded) - 1;
		}
		else if ((*pattern)[i] != '?' && (*pattern)[i] != (*text)[j])
			return (0);
		i--;
		j--;
	}
	resize_value(pattern, 0, i + 1);
	resize_value(text, 0, j + 1);
	return (1);
}
