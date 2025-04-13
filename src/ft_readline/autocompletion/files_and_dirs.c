/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_and_dirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:52:17 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/13 15:15:33 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "dirent.h"

static int	is_special_path_entry(char *value)
{
	return ((value[0] == '.' && !value[1])
		|| (value[0] == '.' && value[1] == '.' && !value[2]));
}

static char	*replace_in_path(char *path, int *i, t_list *envp)
{
	int		len;
	char	*var;
	char	*value;
	char	*tmp;

	len = 0;
	while (path[*i + len] && path[*i + len] != '/')
		len++;
	var = ft_substr(path, *i + 1, len - 1);
	value = get_var_value(var, envp);
	if (!value)
		value = ft_strdup("");
	tmp = path;
	path = ft_strreplace_part(path, *i, len, value);
	free(tmp);
	free(var);
	*i += ft_strlen(value) - 1;
	free(value);
	return (path);
}

char	*replace_variables(char *path, t_list **envp)
{
	int		i;

	if (!envp || !(*envp))
		return (ft_strdup(path));
	i = 0;
	path = ft_strdup(path);
	while (path[i])
	{
		if (path[i] == '$')
			path = replace_in_path(path, &i, *envp);
		i++;
	}
	return (path);
}

static char	*create_element(char *path, char *filename)
{
	char	*joined;
	char	*res;

	joined = ft_pathjoin(path, filename);
	if (ft_isdir(joined))
		res = ft_strjoin(filename, "//");
	else
		res = ft_strdup(filename);
	free(joined);
	return (res);
}

void	add_files_and_dirs_occurences(char *path, char *value,
	t_array *occurences, int *size)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*res;

	path = ft_strdup(path);
	dir = opendir(path);
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		if ((!is_special_path_entry(entry->d_name) || value[0] == '.')
			&& ft_strncmp(entry->d_name, value, ft_strlen(value)) == 0)
		{
			res = create_element(path, entry->d_name);
			add_and_sort_occurence(occurences, res, size);
			free(res);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	free(path);
}
