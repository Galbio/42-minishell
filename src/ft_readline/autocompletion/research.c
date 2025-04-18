/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   research.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:09:10 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/13 15:17:09 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static char	*research_variables(t_readline_data *data, char *prefix, int *size,
	t_list **envp)
{
	t_list	*cur;

	if (!envp || !(*envp))
		return (check_occurence(data, *size));
	cur = *envp;
	while (cur)
	{
		add_variables_occurences(prefix, cur->content, &data->occurences, size);
		cur = cur->next;
	}
	return (check_occurence(data, *size));
}

static char	*research_files_and_dirs(t_readline_data *data, char *prefix,
	int *size)
{
	int				len;
	int				i;
	char			*path;
	char			*value;
	char			*res;

	res = fix_path_prefix(data, &prefix);
	if (res)
		return (res);
	len = ft_strlen(prefix);
	i = len;
	while (i >= 0 && prefix[i] != '/')
		i--;
	path = ft_substr(prefix, 0, i + 1);
	value = ft_substr(prefix, i + 1, len - i - 1);
	add_files_and_dirs_occurences(path, value, &data->occurences, size);
	free(path);
	free(value);
	free(prefix);
	return (check_occurence(data, *size));
}

static char	*research_commands(t_readline_data *data, char *prefix, int *size,
	char ***path)
{
	int		i;

	add_builtins_occurences(prefix, &data->occurences, size);
	if (!path || !(*path))
		return (check_occurence(data, *size));
	i = 0;
	while ((*path)[i])
	{
		add_path_occurences(prefix, (*path)[i], &data->occurences, size);
		i++;
	}
	return (check_occurence(data, *size));
}

char	*research_autocompletion(t_readline_data *data, char *prefix)
{
	int		size;
	int		*max_len;
	char	*slash;

	if (data->tab_pressed)
		ft_array_unset(&data->occurences, ft_array_free_entry);
	data->occurences = ft_array();
	max_len = malloc(sizeof(int));
	*max_len = 0;
	ft_array_push(&data->occurences, max_len);
	size = 1;
	data->tab_pressed = 1;
	slash = ft_strchr(prefix, '/');
	if (prefix[0] == '$' && !slash)
		return (research_variables(data, prefix, &size,
				ft_readline_get_envp_ptr()));
	if (!prefix[0] || prefix[0] == '.' || slash)
		return (research_files_and_dirs(data, prefix, &size));
	if (is_first_argument(data->current))
		return (research_commands(data, prefix, &size,
				ft_readline_get_path_ptr()));
	return (research_files_and_dirs(data, prefix, &size));
}
