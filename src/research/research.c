/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   research.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:48:04 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/04 21:58:39 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "regex.h"

t_array	search_pattern(char *path, char *pattern)
{
	t_array	all;
	int		i;
	t_array	matches;

	all = ft_scandir(path, SCANDIR_SORT_DESCENDING, pattern[0] == '.', 0);
	i = 0;
	matches = ft_array();
	while (i < ft_array_count(all))
	{
		if (regex_match((char *)all[i], pattern))
			ft_array_push(&matches, all[i]);
		else
			free(all[i]);
		i++;
	}
	ft_array_unset(&all, ft_array_nothing_entry);
	return (matches);
}

static int	is_special_path_entry(char *value)
{
	return ((value[0] == '.' && !value[1])
		|| (value[0] == '.' && value[1] == '.' && !value[2]));
}

static t_array	search_matches(char *path, char *first_detail)
{
	t_array	matches;

	if (is_special_path_entry(first_detail))
	{
		matches = ft_array();
		ft_array_push(&matches, ft_strdup(first_detail));
		return (matches);
	}
	return (search_pattern(path, first_detail));
}

static void	process_directory(t_array *res, char *joined, char **path_details)
{
	t_array	rec;
	t_array	new;

	rec = search_pattern_recursive(joined, path_details + 1);
	new = ft_array_merge(*res, rec);
	ft_array_unset(res, ft_array_nothing_entry);
	ft_array_unset(&rec, ft_array_nothing_entry);
	*res = new;
}

t_array	search_pattern_recursive(char *path, char **path_details)
{
	t_array	matches;
	int		i;
	int		size;
	t_array	res;
	char	*joined;

	if (!path_details || !path_details[0])
		return (NULL);
	matches = search_matches(path, path_details[0]);
	if (!path_details[1])
		return (matches);
	i = -1;
	size = ft_array_count(matches);
	res = ft_array();
	while (++i < size)
	{
		joined = ft_pathjoin(path, matches[i]);
		if (ft_isdir(joined))
			process_directory(&res, joined, path_details);
		else if (!path_details[1])
			ft_array_push(&res, ft_strdup(joined + 2));
		free(joined);
	}
	ft_array_unset(&matches, ft_array_free_entry);
	return (res);
}
