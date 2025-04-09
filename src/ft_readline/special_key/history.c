/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:17:19 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/09 13:36:03 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void	update_prompt_position(t_readline_data *data, char *value)
{
	int	i;
	int	count;
	int	v;
	t_vector2	size;

	i = 0;
	count = 0;
	while (value[i])
	{
		if (value[i] == '\n')
			count++;
		i++;
	}
	size = get_terminal_size(data, 0);
	count += (ft_strlen(ft_getlast_newline(value)) / size.x);
	v = data->pos.y + count;
	if (v >= size.y)
		data->pos.y -= v - size.y;
	while (count--)
		write(1, "\n", 1);
}

static void	restore_history(t_readline_data *data, char *value)
{
	int	i;

	data->cursor = data->pos;
	teleport_cursor(data->cursor);
	update_prompt_position(data, value);
	data->cursor = data->pos;
	teleport_cursor(data->cursor);
	i = 0;
	while (value[i])
	{
		process_default_key(data, value + i);
		i++;
	}
	on_write(data);
	write(get_extra_data_in_fd(), CLEAR_TERMINAL_AFTER_CURSOR, 4);
}

void	previous_history_key(t_readline_data *data)
{
	t_readline	*main;
	int			size;

	main = get_readline_struct();
	size = ft_array_count(main->history);
	if (data->history_index >= size)
		return ;
	if (data->history_index == 0)
		data->current_input = data->first;
	else
		free_chars(data->first);
	data->first = NULL;
	data->current = NULL;
	if (data->history_index < size)
		data->history_index++;
	restore_history(data, ((char **)main->history)[data->history_index - 1]);
}

void	next_history_key(t_readline_data *data)
{
	t_readline	*main;

	main = get_readline_struct();
	if (data->history_index <= 0)
		return ;
	free_chars(data->first);
	data->history_index--;
	if (data->history_index == 0)
	{
		data->cursor = data->pos;
		data->first = data->current_input;
		data->current = last_char(data->first);
		data->current_input = NULL;
		on_write(data);
		write(1, "\033[0J", 4);
	}
	else
	{
		data->first = NULL;
		data->current = NULL;
		restore_history(data,
			((char **)main->history)[data->history_index - 1]);
	}
}
