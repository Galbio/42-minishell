/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:50:55 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/03 14:16:20 by lroussel         ###   ########.fr       */
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

int	needed_count(char *pattern)
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

int	find_first_occurrence(char *text, char *pattern, int *pattern_start)
{
	int				i;
	int				j;
	int				finded;
	t_regex_item	*item;
	int				needed;

	needed = needed_count(pattern);
	i = 0;
	j = 0;
	finded = 0;
	while (pattern[i] && pattern[i] != '*' && text[j])
	{
		item = get_regex_item(pattern + i);
		if (item)
		{
			if (regex_item_match(text + j, item->last_finded, item))
			{
				finded++;
				i += ft_strlen(item->last_finded);
			}
			else
			{
				j -= finded;
				i = 0;
				finded = 0;
			}
		}
		else if (pattern[i] == '?' || pattern[i] == text[j])
		{
			finded++;
			i++;
		}
		else
		{
			j -= finded;
			finded = 0;
			i = 0;
		}
		j++;
	}
	*pattern_start = i;
	if (finded == needed)
		return (j);
	return (-1);
}

static int	exit_regex(char *v, char *pat, int res)
{
	free(v);
	free(pat);
	return (res);
}

int	check_middle(char *text, char *pattern)
{
	int	start;
	int	next;
	int	pattern_start;
	int	next_p;

	pattern_start = 0;
	start = 0;
	while (ft_strlen(pattern + pattern_start) > 0)
	{
		if (ft_strlen(pattern + pattern_start) == 1
			&& (pattern + pattern_start)[0] == '*')
			return (1);
		next = find_first_occurrence(text + start,
				pattern + pattern_start, &next_p);
		pattern_start += next_p + 1;
		if (next == -1)
			return (0);
		start += (next);
	}
	return (1);
}

int	len_tests(char *text, char *pattern)
{
	int	len;
	int	max;

	len = ft_strlen(text);
	if (len < min_value_len(pattern))
		return (0);
	max = max_value_len(pattern);
	if (max != -1 && len > max)
		return (0);
	return (1);
}

int	regex_match(char *text, char *pattern)
{
	int		len;

	if (!len_tests(text, pattern))
		return (0);
	text = ft_strdup(text);
	pattern = ft_strdup(pattern);
	if (pattern[0] != '*' && !check_beginning(&text, &pattern))
		return (0);
	if (pattern[ft_strlen(pattern)] != '*' && !check_end(&text, &pattern))
		return (0);
	clean_pattern(&pattern);
	len = ft_strlen(pattern);
	if ((len == 1 && pattern[0] == '*') || (len == 0 && ft_strlen(text) == 0))
		return (exit_regex(text, pattern, 1));
	if (pattern[len - 1] == '*')
		pattern[len - 1] = '\0';
	return (exit_regex(text, pattern, check_middle(text, pattern + 1)));
}
