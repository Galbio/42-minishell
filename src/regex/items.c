/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:43:12 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/03 15:43:22 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

char	*find_regex_item_value(char *text, t_regex_item *item)
{
	int	i;
	int	j;

	i = 3;
	j = 0;
	while (item->format[i - 3] && (item->format[i - 3] != '.'))
	{
		if (!text[j] || (item->format[i - 3] != text[j]))
			return (NULL);
		i++;
		j++;
	}
	while (text[j] && !ft_iswhitespace(text[j])
		&& (text[j] != item->format[i]))
		j++;
	if (!text[j])
		return (NULL);
	while (item->format[i] && text[j])
	{
		if (!text[j] || (item->format[i] != text[j]))
			return (NULL);
		i++;
		j++;
	}
	return (ft_substr(text, 0, j));
}

char	*find_regex_item_value_from_end(char *text, int index,
			t_regex_item *item)
{
	int	i;
	int	j;

	i = ft_strlen(item->format) - 1;
	j = index;
	while (i >= 0 && j >= 0 && item->format[i] != '.')
	{
		if (item->format[i] != text[j])
			return (NULL);
		i--;
		j--;
	}
	i -= 3;
	while (j >= 0 && !ft_iswhitespace(text[j])
		&& !is_another_end(text, j))
		j--;
	while (!is_start(text + j, item->format))
		j++;
	if (j >= (int)ft_strlen(text) || !is_start(text + j, item->format))
		return (0);
	return (ft_substr(text, j, index + 1 - j));
}

t_regex_item	*get_regex_item(char *value)
{
	t_array			*items;
	int				size;
	int				i;
	t_regex_item	*item;

	items = get_regex_items();
	size = ft_array_count(*items);
	i = 0;
	while (i < size)
	{
		item = (*((t_regex_item ***)items))[i];
		free(item->last_finded);
		item->last_finded = find_regex_item_value(value, item);
		if (item->last_finded)
			return (item);
		i++;
	}
	return (NULL);
}

t_regex_item	*get_regex_item_from_end(char *value, int index)
{
	t_array			*items;
	int				size;
	int				i;
	t_regex_item	*item;

	items = get_regex_items();
	size = ft_array_count(*items);
	i = 0;
	while (i < size)
	{
		item = (*((t_regex_item ***)items))[i];
		free(item->last_finded);
		item->last_finded = find_regex_item_value_from_end(value, index, item);
		if (item->last_finded)
			return (item);
		i++;
	}
	return (NULL);
}
