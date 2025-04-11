/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:06:31 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/11 15:22:57 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "dirent.h"

static void	add_and_sort(t_array *res, char *value, int *size)
{
	int	a;
	int	b;
	int	c;
	int	len;
	int	v;

	value = ft_strdup(value);
	if (!value)
		return ;
	if (*size == 0)
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

static void	add_path_values(char *prefix, char *path, t_array *res, int *size)
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
				add_and_sort(res, entry->d_name, size);
			free(joined);
		}
		entry = readdir(dir);
	}

	closedir(dir);
}

static t_array	get_paths_values(char *prefix)
{
	char	***path;
	t_array	res;
	int	size;
	int	i;

	path = ft_readline_get_path_ptr();
	res = ft_array();
	if (!path || !(*path))
		return (res);
	size = 0;
	i = 0;
	while ((*path)[i])
	{
		add_path_values(prefix, (*path)[i], &res, &size);
		i++;
	}
	(void)size;
	return (res);
}

void	display_autocomplatable_commands(char *prefix)
{
	t_array	res;
	int	size;
	int	i;

	res = get_paths_values(prefix);
	size = ft_array_count(res);
	i = 0;	
	printf("\n");
	while (i < size)
	{
		printf("%s ", (char *)res[i]);
		i++;
	}
	printf("\ngood\n");
}
