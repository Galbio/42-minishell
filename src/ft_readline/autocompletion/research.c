/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   research.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:09:10 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/11 23:26:11 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static char	*check_occurence(t_readline_data *data, int size)
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

static char	*research_variables(t_readline_data *data, char *prefix, int *size,
	t_list **envp)
{
	t_list	*cur;

	if (!envp || !(*envp))
		return (NULL);
	cur = *envp;
	while (cur)
	{
		add_variables_occurences(prefix, cur->content, &data->occurences, size);
		cur = cur->next;
	}
	return (check_occurence(data, *size));
}

//TODO; for later
static char	*research_files(t_readline_data *data, char *prefix, int *size)
{
	(void)data;
	(void)prefix;
	(void)size;
	return (NULL);
}

static char	*research_commands(t_readline_data *data, char *prefix, int *size,
	char ***path)
{
	int		i;

	add_builtins_occurences(prefix, &data->occurences, size);
	if (!path || !(*path))
		return (NULL);
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

	if (data->tab_pressed)
		ft_array_unset(&data->occurences, ft_array_free_entry);
	data->occurences = ft_array();
	max_len = malloc(sizeof(int));
	*max_len = 0;
	ft_array_push(&data->occurences, max_len);
	size = 1;
	data->tab_pressed = 1;
	if (prefix[0] == '$')
		return (research_variables(data, prefix, &size,
				ft_readline_get_envp_ptr()));
	if (prefix[0] == '.')
		return (research_files(data, prefix, &size));
	if (is_first_argument(data->current))
		return (research_commands(data, prefix, &size,
				ft_readline_get_path_ptr()));
	return (research_files(data, prefix, &size));
}
