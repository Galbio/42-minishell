/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 21:40:05 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/27 04:24:42 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	sort_array(t_array *array)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = ft_array_count(*array);
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strncmp((char *)(*array)[i], (char *)(*array)[j],
									ft_strlen((char *)(*array)[i])) > 0)
				ft_array_swap(array, i, j);
			j++;
		}
		i++;
	}
}

t_array	ft_scandir(char *path, int hidden_files, int dir_path)
{
	DIR				*dir;
	t_array			array;
	struct dirent	*entry;

	dir = opendir(path);
	array = ft_array();
	entry = readdir(dir);
	while (entry)
	{
		if (!dir_path && entry->d_name[0] == '.' && (!entry->d_name[1]
				|| (entry->d_name[1] == '.' && !entry->d_name[2])))
		{
			entry = readdir(dir);
			continue ;
		}
		if (hidden_files || entry->d_name[0] != '.')
			ft_array_push(&array, ft_strdup(entry->d_name));
		entry = readdir(dir);
	}
	closedir(dir);
	return (array);
}
*/
void	nothing(int key, void *value)
{
	(void)key;
	(void)value;
}

t_list	*process_wildcards(char *path, char *pattern)
{
	t_array	all;
	int		size;
	int		i;
	t_list	*head;
	t_list	*cur;

	all = ft_scandir(path, SCANDIR_SORT_DESCENDING, pattern[0] == '.', 0);
	size = ft_array_count(all);
	i = 0;
	head = NULL;
	while (i < size)
	{
		if (match((char *)all[i], pattern))
		{
			if (!head)
			{
				head = ft_lstnew(all[i]);
				cur = head;
			}
			else
			{
				cur->next = ft_lstnew(all[i]);
				cur = cur->next;
			}
		}
		else
			free(all[i]);
		i++;
	}
	ft_array_unset(&all, nothing);
	return (head);
}
