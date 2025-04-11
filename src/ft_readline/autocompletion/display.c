/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:06:31 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/11 16:15:15 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "dirent.h"

static void	add_and_sort(t_array *res, char *value, int *size)
{
	int	i;
	int	index;
	int	len;
	int	diff;

	value = ft_strdup(value);
	if (!value)
		return ;
	if (*size == 0)
	{
		(*size)++;
		ft_array_push(res, value);
		return ;
	}
	len = ft_strlen(value);
	i = 0;
	index = *size;
	while (i < *size)
	{
		diff = ft_strncmp((*res)[i], value, ft_max(len, ft_strlen((char *)(*res)[i])));
		if (diff == 0)
			return ;
		if (diff > 0)
		{
			index = i;
			break ;
		}
		i++;
	}
	if (index == *size)
		ft_array_push(res, value);
	else
		ft_array_add(res, index, value);
	(*size)++;
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
			joined = ft_pathjoin(path, entry->d_name);
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
