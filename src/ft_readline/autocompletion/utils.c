/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:30:43 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/13 15:19:35 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static int	check_all(t_array *occurences, char **value, int *size, int len)
{
	*value = ft_strdup(*value);
	if (!(*value))
		return (0);
	if (len > *((int *)(*occurences)[0]))
		*((int *)(*occurences)[0]) = len - ((*value)[len - 1] == '/');
	if (*size == 1)
	{
		(*size)++;
		ft_array_push(occurences, *value);
		return (0);
	}
	return (1);
}

static void	add_value(t_array *occurences, char *value, int index, int *size)
{
	if (index == *size)
		ft_array_push(occurences, value);
	else
		ft_array_add(occurences, index, value);
	(*size)++;
}

void	add_and_sort_occurence(t_array *occurences, char *value, int *size)
{
	int	len;
	int	i;
	int	index;
	int	diff;

	len = ft_strlen(value);
	if (!check_all(occurences, &value, size, len))
		return ;
	i = 0;
	index = *size;
	while (++i < *size)
	{
		diff = ft_strncmp((*occurences)[i], value,
				ft_max(len, ft_strlen((char *)(*occurences)[i])));
		if (diff == 0)
		{
			free(value);
			return ;
		}
		if (index == *size && diff > 0)
			index = i;
	}
	add_value(occurences, value, index, size);
}

char	*check_occurence(t_readline_data *data, int size)
{
	char	*value;

	if (size == 2)
	{
		value = ft_strdup((char *)data->occurences[1]);
		ft_array_unset(&data->occurences, ft_array_free_entry);
		data->tab_pressed = 0;
		return (value);
	}
	return (NULL);
}

char	*fix_path_prefix(t_readline_data *data, char **prefix)
{
	char			*tmp;

	*prefix = replace_variables(*prefix, ft_readline_get_envp_ptr());
	if ((*prefix)[0] == '.' && !(*prefix)[1]
		&& is_first_argument(data->current))
	{
		tmp = ft_strjoin(*prefix, "/");
		free(*prefix);
		return (tmp);
	}
	if ((*prefix)[0] != '/' && !((*prefix)[0] == '.'
			&& ((*prefix)[1] == '/'
				|| ((*prefix)[1] == '.' && (*prefix)[2] == '/'))))
	{
		tmp = *prefix;
		*prefix = ft_pathjoin(".", *prefix);
		free(tmp);
	}
	return (NULL);
}
