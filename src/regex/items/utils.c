/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:43:35 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/03 15:50:05 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

int	is_start(char *value, char *format)
{
	int	i;

	i = 0;
	while (format[i] && value[i] && format[i] != '.')
	{
		if (!value[i] || (format[i] != value[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*get_end(char *format)
{
	int	i;

	i = 0;
	while (format[i] && format[i] != '.')
		i++;
	return (format + i + 3);
}

int	is_end(char *value, char *format)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	format = get_end(format);
	while (format[i] && value[j])
	{
		if (!value[j] || (format[i] != value[j]))
			return (0);
		i++;
		j++;
	}
	return (1);
}

int	is_another_end(char *text, int index)
{
	t_array			*items;
	int				size;
	int				i;
	t_regex_item	*item;
	int				j;

	items = get_regex_items();
	size = ft_array_count(*items);
	i = 0;
	while (i < size)
	{
		item = (*((t_regex_item ***)items))[i];
		j = index - ft_strlen(get_end(item->format));
		if (is_end(text + j, item->format))
			return (1);
		i++;
	}
	return (0);
}
