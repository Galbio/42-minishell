/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:50:55 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/01 17:47:59 by lroussel         ###   ########.fr       */
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
	int		i;
	int		j;
	char	*brackets;

	i = 0;
	j = 0;
	while ((*pattern)[i] && (*pattern)[i] != '*')
	{
		brackets = find_brackets((*pattern) + i);
		if (brackets)
		{
			if (!brackets_match((*text)[j], brackets))
			{
				free(brackets);
				return (0);
			}
			i += ft_strlen(brackets) - 1;
			free(brackets);
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
	int		i;
	int		j;
	char	*brackets;

	i = ft_strlen(*pattern) - 1;
	j = ft_strlen(*text) - 1;
	while (i >= 0 && (*pattern)[i] != '*')
	{
		brackets = find_brackets_from_end((*pattern), i);
		if (brackets)
		{
			if (!brackets_match((*text)[j], brackets))
			{
				free(brackets);
				return (0);
			}
			i -= ft_strlen(brackets) - 1;
			free(brackets);
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
	int		i;
	int		needed;
	char	*brackets;

	i = 0;
	needed = 0;
	while (pattern[i] && pattern[i] != '*')
	{
		if (have_brackets(pattern + i))
		{
			brackets = find_brackets(pattern + i);
			if (brackets)
				i += ft_strlen(brackets) - 1;
		}
		needed++;
		i++;
	}
	return (needed);
}

int	needed_count_end(char *pattern)
{
	int		i;
	int		needed;
	char	*brackets;

	i = ft_strlen(pattern) - 1;
	needed = 0;
	while (i > 0 && pattern[i] != '*')
	{
		if (pattern[i] == ']')
		{
			brackets = find_brackets_from_end(pattern, i);
			if (brackets)
				i -= ft_strlen(brackets) - 1;
			free(brackets);
		}
		needed++;
		i--;
	}
	return (needed);
}

int	find_first_occurrence(char *text, char *pattern, int *pattern_start)
{
	int		i;
	int		j;
	int		finded;
	char	*brackets;
	int		needed;

	needed = needed_count(pattern);
	i = 0;
	j = 0;
	finded = 0;
	while (pattern[i] && pattern[i] != '*' && text[j])
	{
		brackets = find_brackets(pattern + i);
		if (brackets)
		{
			if (brackets_match(text[j], brackets))
			{
				finded++;
				i += ft_strlen(brackets);
			}
			else
			{
				j -= finded;
				i = 0;
				finded = 0;
			}
			free(brackets);
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

int	find_last_occurrence(char *text, char *pattern, int *pattern_end)
{
	int		i;
	int		j;
	int		finded;
	int		needed;
	char	*brackets;

	needed = needed_count_end(pattern);
	i = ft_strlen(pattern) - 1;
	j = ft_strlen(text) - 1;
	finded = 0;
	while (i >= 0 && pattern[i] != '*' && j >= 0)
	{
		brackets = find_brackets_from_end(pattern, i);
		if (brackets)
		{
			if (brackets_match(text[j], brackets))
			{
				finded++;
				i -= ft_strlen(brackets);
			}
			else
			{
				j += finded;
				i = ft_strlen(pattern) - 1;
				finded = 0;
			}
			free(brackets);
		}
		else if (pattern[i] == '?' || pattern[i] == text[j])
		{
			finded++;
			i--;
		}
		else
		{
			j += finded;
			finded = 0;
			i = ft_strlen(pattern) - 1;
		}
		j--;
	}
	*pattern_end = i;
	if (finded == needed)
		return (j + 1);
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
	int	end;
	int	pattern_start;
	int	pattern_end;

	if (ft_strlen(pattern) == 0)
		return (1);
	start = find_first_occurrence(text, pattern, &pattern_start);
	if (start == -1)
		return (0);
	if (!ft_strchr(pattern, '*'))
		return (1);
	end = find_last_occurrence(text, pattern, &pattern_end);
	if (end == -1)
		return (0);
	if (end <= (start - 1))
		return (0);
	if (pattern_start == pattern_end || pattern_end == -1)
		return (1);
	text = ft_substr(text, start, end - 1);
	pattern = ft_substr(pattern, pattern_start + 1,
			pattern_end - pattern_start - 1);
	return (exit_regex(text, pattern, check_middle(text, pattern)));
}

int	basic_tests(char *text, char *pattern)
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

	if (!basic_tests(text, pattern))
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

void	nothing(int key, void *value)
{
	(void)key;
	(void)value;
}

static void	add_to_list(t_list **head, t_list **cur, void *value)
{
	if (!(*head))
	{
		*head = ft_lstnew(value);
		*cur = *head;
		return ;
	}
	(*cur)->next = ft_lstnew(value);
	*cur = (*cur)->next;
}

t_list	*process_wildcards(char *path, char *pattern)
{
	t_array	all;
	int		i;
	t_list	*head;
	t_list	*cur;

	all = ft_scandir(path, SCANDIR_SORT_DESCENDING, pattern[0] == '.', 0);
	i = 0;
	head = NULL;
	while (i < ft_array_count(all))
	{
		if (regex_match((char *)all[i], pattern))
			add_to_list(&head, &cur, all[i]);
		else
			free(all[i]);
		i++;
	}
	ft_array_unset(&all, nothing);
	return (head);
}
