/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:06:31 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/11 23:53:19 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "dirent.h"

static void	add_and_sort(t_array *occurences, char *value, int *size)
{
	int	a;
	int	b;
	int	c;
	int	len;
	int	v;

	value = ft_strdup(value);
	if (!value)
		return ;
	len = ft_strlen(value);
	if (len > *((int *)(*occurences)[0]))
		*((int *)(*occurences)[0]) = len;
	if (*size == 1)
	{
		ft_array_push(res, value);
		return ;
	}
	a = 0;
	b = *size;
	c = b / 2;
	len = ft_strlen(value);
	v = ft_strncmp((*res)[c], value, ft_max(len, ft_strlen((char *)(*res)[c])));
	while (b - a > 0)
	{
		if (v == 0)
			return ;
		if (v < 0)
			b = c;
		else
			a = c;
		c = (b - a) / 2;
	}
	ft_array_add(res, c, value);
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
			joined = ft_pathjoin(path, ft_strdup(entry->d_name));
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

static void	print_values(t_array occurences, int size, int col, int max)
{
	int		i;
	int		j;
	char	*value;
	int		len;

	printf("\n");
	i = 1;
	while (i < size)
	{
		value = (char *)occurences[i];
		len = ft_strlen(value);
		if (value[len - 1] == '/')
			value[len - 1] = '\0';
		printf("%s", (char *)occurences[i]);
		j = 0;
		while (j < max - len)
		{
			printf(" ");
			j++;
		}
		i++;
		if ((i - 1) % col == 0)
			printf("\n");
	}
	printf("\n");
}

void	display_autocompletion(t_readline_data *data)
{
	t_vector2	tsize;
	int			max;
	int			col;
	int			size;

	if (!data->tab_pressed)
		return ;
	data->tab_pressed = 0;
	size = ft_array_count(data->occurences);
	if (size == 1)
	{
		ft_array_unset(&data->occurences, ft_array_free_entry);
		return ;
	}
	tsize = get_terminal_size(data, 1);
	max = *((int *)data->occurences[0]) + 1;
	col = tsize.x / max;
	print_values(data->occurences, size, col, max);
	data->cursor.y += size / col + 2;
	if (data->cursor.y > tsize.y)
		data->cursor.y = tsize.y;
	ft_array_unset(&data->occurences, ft_array_free_entry);
}
