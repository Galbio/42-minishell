/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   research.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:09:10 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/11 21:11:13 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static char	*research_variables(t_readline_data *data, char *prefix, int *size)
{
	(void)data;
	(void)prefix;
	(void)size;
	return (NULL);
}

static char	*research_files(t_readline_data *data, char *prefix, int *size)
{
	(void)data;
	(void)prefix;
	(void)size;
	return (NULL);
}

static char	*research_commands(t_readline_data *data, char *prefix, int *size)
{
	char	***path;
	int		i;
	char	*value;

	add_builtins_occurences(prefix, &data->occurences, size);
	path = ft_readline_get_path_ptr();
	if (!path || !(*path))
		return (NULL);
	i = 0;
	while ((*path)[i])
	{
		add_path_occurences(prefix, (*path)[i], &data->occurences, size);
		i++;
	}
	if (*size == 2)
	{
		value = ft_strdup((char *)data->occurences[1]);
		ft_array_unset(&data->occurences, ft_array_free_entry);
		data->tab_pressed = 0;
		return (value);
	}
	return (NULL);
}

char	*research_autocompletion(t_readline_data *data, char *prefix)
{
	int		size;
	int		*max_len;

	if (data->tab_pressed)
		ft_array_unset(&data->occurences, ft_array_free_entry);
	data->occurences = ft_array();
	max_len = malloc(sizeof(int));
	*max_len = 0;
	ft_array_push(&data->occurences, max_len);
	size = 1;
	data->tab_pressed = 1;
	if (is_first_argument(data->current))
		return (research_commands(data, prefix, &size));
	if (prefix[0] == '$')
		return (research_variables(data, prefix, &size));
	return (research_files(data, prefix, &size));
}
