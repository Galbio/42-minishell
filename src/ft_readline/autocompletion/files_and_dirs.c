/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_and_dirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:52:17 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/13 13:47:56 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "dirent.h"

static int	is_special_path_entry(char *value)
{
	return ((value[0] == '.' && !value[1])
		|| (value[0] == '.' && value[1] == '.' && !value[2]));
}

static int	check_dir(DIR **dir, char *path)
{
	*dir = opendir(path);
	if (!(*dir))
		return (0);
	return (1);
}

void	add_files_and_dirs_occurences(char *path, char *value,
	t_array *occurences, int *size)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*joined;
	char			*res;

	if (!check_dir(&dir, path))
		return ;
	entry = readdir(dir);
	while (entry)
	{
		if ((!is_special_path_entry(entry->d_name) || value[0] == '.')
			&& ft_strncmp(entry->d_name, value, ft_strlen(value)) == 0)
		{
			joined = ft_pathjoin(path, entry->d_name);
			if (ft_isdir(joined))
				res = ft_strjoin(entry->d_name, "//");
			else
				res = ft_strdup(entry->d_name);
			add_and_sort_occurence(occurences, res, size);
			free(res);
			free(joined);
		}
		entry = readdir(dir);
	}
	closedir(dir);
}
