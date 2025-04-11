/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:24:27 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/11 20:59:47 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "dirent.h"

void	add_builtins_occurences(char *prefix, t_array *occurences, int *size)
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
		add_and_sort_occurence(occurences, "echo", size);
	if (ft_strncmp(prefix, "cd", ft_min(len, 3)) == 0)
		add_and_sort_occurence(occurences, "cd", size);
	if (ft_strncmp(prefix, "pwd", b) == 0)
		add_and_sort_occurence(occurences, "pwd", size);
	if (ft_strncmp(prefix, "export", ft_min(len, 7)) == 0)
		add_and_sort_occurence(occurences, "export", size);
	if (ft_strncmp(prefix, "unset", c) == 0)
		add_and_sort_occurence(occurences, "unset", size);
	if (ft_strncmp(prefix, "env", b) == 0)
		add_and_sort_occurence(occurences, "env", size);
	if (ft_strncmp(prefix, "exit", a) == 0)
		add_and_sort_occurence(occurences, "exit", size);
	if (ft_strncmp(prefix, "alias", c) == 0)
		add_and_sort_occurence(occurences, "alias", size);
}

void	add_path_occurences(char *prefix, char *path,
			t_array *occurences, int *size)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*joined;

	dir = opendir(path);
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.'
			&& ft_strncmp(entry->d_name, prefix, ft_strlen(prefix)) == 0)
		{
			joined = ft_pathjoin(path, entry->d_name);
			if (access(joined, X_OK) == 0 && !ft_isdir(joined))
				add_and_sort_occurence(occurences, entry->d_name, size);
			free(joined);
		}
		entry = readdir(dir);
	}
	closedir(dir);
}
