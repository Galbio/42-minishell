/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:06:31 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/11 19:12:00 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "dirent.h"

static void	add_and_sort(t_array *occurences, char *value, int *size)
{
	int	i;
	int	index;
	int	len;
	int	diff;
	int	finded;

	value = ft_strdup(value);
	if (!value)
		return ;
	len = ft_strlen(value);
	if (len > *((int *)(*occurences)[0]))
		*((int *)(*occurences)[0]) = len;
	if (*size == 1)
	{
		(*size)++;
		ft_array_push(occurences, value);
		return ;
	}
	i = 1;
	index = *size;
	finded = 0;
	while (i < *size)
	{
		diff = ft_strncmp((*occurences)[i], value, ft_max(len, ft_strlen((char *)(*occurences)[i])));
		if (diff == 0)
		{
			free(value);
			return ;
		}
		if (!finded && diff > 0)
		{
			index = i;
			finded = 1;
		}
		i++;
	}
	if (index == *size)
		ft_array_push(occurences, value);
	else
		ft_array_add(occurences, index, value);
	(*size)++;
}

static void	add_path_values(char *prefix, char *path, t_array *occurences, int *size)
{
	DIR				*dir;
	struct dirent	*entry;
	char	*joined;

	dir = opendir(path);
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && ft_strncmp(entry->d_name, prefix, ft_strlen(prefix)) == 0)
		{
			joined = ft_pathjoin(path, entry->d_name);
			if (access(joined, X_OK) == 0 && !ft_isdir(joined))
				add_and_sort(occurences, entry->d_name, size);
			free(joined);
		}
		entry = readdir(dir);
	}

	closedir(dir);
}

static void	get_paths_values(char *prefix, t_array *occurences, int *size)
{
	char	***path;
	int	i;

	path = ft_readline_get_path_ptr();
	if (!path || !(*path))
		return ;
	i = 0;
	while ((*path)[i])
	{
		add_path_values(prefix, (*path)[i], occurences, size);
		i++;
	}
}

static void	add_builtins(char *prefix, t_array *occurences, int *size)
{
	int	len;
	int	a;
	int	b;
	int	c;

	len = ft_strlen(prefix);
	a = ft_min(len, 5);
	b = ft_min(len, 4);
	c = ft_min(len, 6);
	if (ft_strncmp(prefix, "echo", a) == 0)
		add_and_sort(occurences, "echo", size);
	if (ft_strncmp(prefix, "cd", ft_min(len, 3)) == 0)
		add_and_sort(occurences, "cd", size);
	if (ft_strncmp(prefix, "pwd", b) == 0)
		add_and_sort(occurences, "pwd", size);
	if (ft_strncmp(prefix, "export", ft_min(len, 7)) == 0)
		add_and_sort(occurences, "export", size);
	if (ft_strncmp(prefix, "unset", c) == 0)
		add_and_sort(occurences, "unset", size);
	if (ft_strncmp(prefix, "env", b) == 0)
		add_and_sort(occurences, "env", size);
	if (ft_strncmp(prefix, "exit", a) == 0)
		add_and_sort(occurences, "exit", size);
	if (ft_strncmp(prefix, "alias", c) == 0)
		add_and_sort(occurences, "alias", size);
}

void	display_autocompletion(t_readline_data *data)
{
	int	i;
	t_vector2	tsize;
	int	max;
	int	col;
	int	j;
	int	size;

	if (!data->tab_pressed)
		return ;
	data->tab_pressed = 0;
	size = ft_array_count(data->occurences);
	if (size == 1)
		return ;
	tsize = get_terminal_size(data, 1);
	max = *((int *)data->occurences[0]) + 1;
	col = tsize.x / max;
	i = 1;
	printf("\n");
	while (i < size)
	{
		printf("%s", (char *)data->occurences[i]);
		j = 0;
		while (j < (int)(max - ft_strlen((char *)data->occurences[i])))
		{
			printf(" ");
			j++;
		}
		i++;
		if (i % col == 0)
			printf("\n");
	}
	printf("\n");
	data->cursor.y += size / col + 2;
	if (data->cursor.y > tsize.y)
		data->cursor.y = tsize.y;
	ft_array_unset(&data->occurences, ft_array_free_entry);
}

char	*research_autocompletion(t_readline_data *data, char *prefix)
{
	int	size;
	char	*value;
	int	*max_len;

	if (!is_first_argument(data->current))
		return (NULL);
	if (data->tab_pressed)
		ft_array_unset(&data->occurences, ft_array_free_entry);
	data->occurences = ft_array();
	max_len = malloc(sizeof(int));
	*max_len = 0;
	ft_array_push(&data->occurences, max_len);
	size = 1;
	add_builtins(prefix, &data->occurences, &size);
	get_paths_values(prefix, &data->occurences, &size);
	if (size == 2)
	{
		value = ft_strdup((char *)data->occurences[1]);
		ft_array_unset(&data->occurences, ft_array_free_entry);
		return (value);
	}
	data->tab_pressed = 1;
	return (NULL);
}
