/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_occurence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:33:42 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/03 16:46:39 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

static int	needed_count(char *pattern)
{
	int				i;
	int				needed;
	t_regex_item	*item;

	i = 0;
	needed = 0;
	while (pattern[i] && pattern[i] != '*')
	{
		item = get_regex_item(pattern + i);
		if (item)
			i += ft_strlen(item->last_finded) - 1;
		needed++;
		i++;
	}
	return (needed);
}

static void	on_find(int *finded, int *i, int len)
{
	(*finded)++;
	*i += len;
}

static void	reset_values(int *j, int *finded, int *i)
{
	*j -= *finded;
	*i = 0;
	*finded = 0;
}

static int	init_values(int *i, int *j, int *finded, int needed_count)
{
	*i = 0;
	*j = 0;
	*finded = 0;
	return (needed_count);
}

int	find_first_occurrence(char *text, char *pattern, int *pattern_start)
{
	int				i;
	int				j;
	int				finded;
	t_regex_item	*item;
	int				needed;

	needed = init_values(&i, &j, &finded, needed_count(pattern));
	while (pattern[i] && pattern[i] != '*' && text[j])
	{
		item = get_regex_item(pattern + i);
		if (item)
		{
			if (regex_item_match(text + j, item->last_finded, item))
				on_find(&finded, &i, ft_strlen(item->last_finded));
			else
				reset_values(&j, &finded, &i);
		}
		else if (pattern[i] == '?' || pattern[i] == text[j])
			on_find(&finded, &i, 1);
		else
			reset_values(&j, &finded, &i);
		j++;
	}
	*pattern_start = i;
	return (((finded == needed) * (j + 1)) - 1);
}
