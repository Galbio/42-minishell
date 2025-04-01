/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:50:55 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/01 15:48:52 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

int	check_beginning(char **text, char **pattern)
{
	int	i;
	int	j;
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
		}
		else if ((*pattern)[i] != '?' && (*pattern)[i] != (*text)[j])
			return (0);
		i++;
		j++;
	}

	char	*new;
	new = ft_substr(*pattern, i, ft_strlen(*pattern) - i);
	free(*pattern);
	*pattern = new;
	char	*new2;
	new2 = ft_substr(*text, j, ft_strlen(*text) - j);
	free(*text);
	*text = new2;
	return (1);
}

int	check_end(char **text, char **pattern)
{
	int	i;
	int	j;
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
		}
		else if ((*pattern)[i] != '?' && (*pattern)[i] != (*text)[j])
			return (0);
		i--;
		j--;
	}
	char	*new;
	new = ft_substr(*pattern, 0, i + 1);
	free(*pattern);
	*pattern = new;
	char	*new2;
	new2 = ft_substr(*text, 0, j + 1);
	free(*text);
	*text = new2;
	return (1);
}

void	clean_pattern(char **pattern)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while ((*pattern)[i])
	{
		if ((*pattern)[i] == '*')
			while ((*pattern)[i + 1] && (*pattern)[i + 1] == '*')
				i++;
		i++;
		count++;
	}
	char	*new = malloc(sizeof(char) * (count + 1));
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
	int	i;
	int	needed;
	char	*brackets;

	i = 0;
	needed = 0;
	while (pattern[i] && pattern[i] != '*')
	{
		if (have_brackets(pattern + i))
		{
			while (pattern[i + 1] == '[')
				i++;
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
	int	i;
	int	needed;
	char	*brackets;
	int	len;

	i = ft_strlen(pattern) - 1;
	needed = 0;
	while (i > 0 && pattern[i] != '*')
	{
		if (pattern[i] == ']')
		{
			len = 0;
			while (pattern[i - len] != '[')
				len++;
			brackets = find_brackets(pattern + i - len);
			if (brackets)
			{
				i -= len;
				while (i >= 0 && pattern[i - 1] == '[')
					i--;
			}
			else
			{
				needed += len;
				i--;
			}
			free(brackets);
		}
		needed++;
		i--;
	}
	return (needed);
}

int	find_first_occurrence(char *text, char *pattern, int *ip)
{
	int	i;
	int	j;
	int	finded;
	char	*brackets;
	int	needed;
	finded = 0;
	
	needed = needed_count(pattern);
	i = 0;
	j = 0;
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
	*ip = i;
	if (finded == needed)
		return (j);
	return (-1);
}

int	find_last_occurrence(char *text, char *pattern, int *ip)
{
	int	i;
	int	j;
	int	finded;
	int	needed;
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
	*ip = i;
	if (finded == needed)
		return (j + 1);
	return (-1);
}

int	check_middle(char *text, char *pattern)
{
	int	i;
	int	j;
	int	ip;
	int	jp;
	char	*newt;
	char	*newp;
	int	res;
	
	if (ft_strlen(pattern) == 0)
		return (1);
	if (!ft_strchr(pattern, '*'))
	{
		if (find_first_occurrence(text, pattern, &ip) != -1)
			return (1);
		return (0);
	}
	i = find_first_occurrence(text, pattern, &ip);
	if (i == -1)
		return (0);
	j = find_last_occurrence(text, pattern, &jp);
	if (j == -1)
		return (0);
	if (j <= (i - 1))
		return (0);
	if (ip == jp || jp == -1)
		return (1);
	j--;
	newt = ft_substr(text, i, j);
	newp = ft_substr(pattern, ip + 1, jp - ip - 1);
	res = check_middle(newt, newp);
	free(newt);
	free(newp);
	return (res);
}

int	regex_match(char *text, char *pattern)
{
	char	*v;
	char	*pat;
	int	len;
	int	max;
	int	res;

	v = ft_strdup(text);
	pat = ft_strdup(pattern);
	len = ft_strlen(text);
	if (len < min_value_len(pat))
		return (0);
	max = max_value_len(pat);
	if (max != -1 && len > max)
		return (0);
	if (!check_beginning(&v, &pat))
		return (0);
	if (!check_end(&v, &pat))
		return (0);
	clean_pattern(&pat);
	len = ft_strlen(pat);
	if ((len == 1 && pat[0] == '*') || (len == 0 && ft_strlen(v) == 0))
	{
		free(v);
		free(pat);
		return (1);
	}
	if (pat[len - 1] == '*')
		pat[len - 1] = '\0';
	res = check_middle(v, pat + 1);
	free(v);
	free(pat);
	return (res);
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
