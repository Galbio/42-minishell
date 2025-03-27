/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:50:55 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/27 05:13:02 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_question_or_match(char *text, char *pattern, int *i, int *j)
{
	if (pattern[*j] == '?' || pattern[*j] == text[*i])
	{
		(*i)++;
		(*j)++;
		return (1);
	}
	return (0);
}

void	handle_star(int *j, int *start_index, int *match, int i)
{
	*start_index = *j;
	*match = i;
	(*j)++;
}

int	backtrack(int *j, int *match, int *i, int start_index)
{
	if (start_index != -1)
	{
		*j = start_index + 1;
		(*match)++;
		*i = *match;
		return (1);
	}
	return (0);
}

int	check_remaining_pattern(char *pattern, int j, int m)
{
	while (j < m && pattern[j] == '*')
		j++;
	return (j == m);
}

int	regex_match(char *text, char *pattern)
{
	int	n;
	int	m;
	int	i;
	int	j;
	int	start_index;
	int	match;

	n = ft_strlen(text);
	m = ft_strlen(pattern);
	i = 0;
	j = 0;
	start_index = -1;
	match = 0;
	while (i < n)
	{
		if (j < m && handle_question_or_match(text, pattern, &i, &j))
			continue ;
		else if (j < m && pattern[j] == '*')
			handle_star(&j, &start_index, &match, i);
		else if (backtrack(&j, &match, &i, start_index))
			continue ;
		else
			return (0);
	}
	return (check_remaining_pattern(pattern, j, m));
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
