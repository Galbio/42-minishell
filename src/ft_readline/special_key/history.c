/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:17:19 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/26 18:14:54 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	restore_history(t_readline_data *data, char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		process_default_key(data, value + i);
		i++;
	}
	on_write(data);
}

void	previous_history_key(t_readline_data *data)
{
	t_readline	*core;
	int			size;

	core = get_readline_core();
	size = ft_array_count(core->history);
	if (data->history_index >= size)
		return ;
	if (data->history_index == 0)
		data->current_input = data->first;
	else
		free_chars(data->first);
	data->first = NULL;
	data->actual = NULL;
	if (data->history_index < size)
		data->history_index++;
	restore_history(data, ((char **)core->history)[data->history_index - 1]);
}

void	next_history_key(t_readline_data *data)
{
	t_readline	*core;

	core = get_readline_core();
	if (data->history_index <= 0)
		return ;
	free_chars(data->first);
	data->history_index--;
	if (data->history_index == 0)
	{
		data->first = data->current_input;
		data->actual = last_char(data->first);
		data->current_input = NULL;
		on_write(data);
	}
	else
	{
		data->first = NULL;
		data->actual = NULL;
		restore_history(data,
			((char **)core->history)[data->history_index - 1]);
	}
}
