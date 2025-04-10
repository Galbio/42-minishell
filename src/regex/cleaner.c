/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:33:19 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/04 22:12:20 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

static int	cleaned_len(char *pattern)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (pattern[i])
	{
		if (pattern[i] == '*')
			while (pattern[i + 1] && pattern[i + 1] == '*')
				i++;
		i++;
		count++;
	}
	return (count);
}

void	clean_pattern(char **pattern)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(sizeof(char) * (cleaned_len(*pattern) + 1));
	if (!new)
		return ;
	i = 0;
	j = 0;
	while ((*pattern)[i])
	{
		if ((*pattern)[i] == '*')
			while ((*pattern)[i + 1] && (*pattern)[i + 1] == '*')
				i++;
		new[j] = (*pattern)[i];
		i++;
		j++;
	}
	new[j] = '\0';
	free(*pattern);
	*pattern = new;
}

static void	free_item_entry(int key, void *value)
{
	(void)key;
	free(((t_regex_item *)value)->last_finded);
	free(value);
}

void	free_regex_items(void)
{
	t_array	*items;

	items = get_regex_items();
	ft_array_unset(items, free_item_entry);
	free(items);
}
