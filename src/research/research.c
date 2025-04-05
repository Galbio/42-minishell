/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   research.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:48:04 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/05 18:15:31 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "regex.h"

t_list	*search_pattern(char *path, char *pattern)
{
	t_array	all;
	int		i;
	t_list	*matches;

	all = ft_scandir(path, SCANDIR_SORT_DESCENDING, pattern[0] == '.', 0);
	i = 0;
	matches = NULL;
	while (i < ft_array_count(all))
	{
		if (regex_match((char *)all[i], pattern))
			ft_lstadd_back(&matches, ft_lstnew(all[i]));
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

static t_list	*add_prefixes(char *prefix, t_list *list)
{
	t_list	*cur;
	char	*temp;
	char	*joined;

	if (!prefix || !prefix[0])
		return (list);
	cur = list;
	while (cur)
	{
		temp = cur->content;
		joined = ft_pathjoin(prefix, temp);
		if (prefix[0] != '.')
			cur->content = joined;
		else
		{
			cur->content = ft_strdup(joined + 1
					+ (prefix[1] == '\0' || prefix[1] == '/'));
			free(joined);
		}
		free(temp);
		cur = cur->next;
	}
	return (list);
}

static t_list	*search_matches(char *base_path, char *to_check)
{
	char	*cleaned;
	t_list	*res;
	char	*prefix;

	cleaned = ft_strtrim(to_check, "/");
	prefix = ft_substr(to_check, 0, ft_strlen(to_check) - ft_strlen(cleaned));
	if (is_special_path_entry(cleaned))
		res = ft_lstnew(ft_strdup(cleaned));
	else
		res = search_pattern(base_path, cleaned);
	add_prefixes(prefix, res);
	free(cleaned);
	free(prefix);
	return (res);
}

t_list	*search_pattern_recursive(char *base_path, char **path)
{
	t_list	*matches;
	t_list	*cur;
	t_list	*res;
	char	*joined;

	if (!path || !path[0])
		return (NULL);
	matches = search_matches(base_path, path[0]);
	if (!path[1])
		return (add_prefixes(base_path, matches));
	res = NULL;
	cur = matches;
	while (cur)
	{
		joined = ft_pathjoin(base_path, cur->content);
		if (ft_isdir(joined))
			ft_lstadd_back(&res, search_pattern_recursive(joined, path + 1));
		else if (!path[1])
			ft_lstadd_back(&res, ft_lstnew(ft_strdup(joined + 2)));
		free(joined);
		cur = cur->next;
	}
	ft_lstclear(&matches, free);
	return (res);
}
