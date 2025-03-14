/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:11:06 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/14 12:33:17 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	on_press_delete_key(t_readline *data)
{
	t_char	*c;

	if (!data->actual)
		return ;
	if (data->actual == data->first)
	{
		data->first = data->first->next;
		remove_char(&data->actual);
		data->actual = NULL;
		on_delete(data);
		return ;
	}
	c = data->actual;
	remove_char(&data->actual);
	if (data->actual != c)
		data->size--;
	if (!data->actual && data->size == 0)
		data->first = NULL;
	on_delete(data);
}

void	on_press_left_arrow_key(t_readline *data)
{
	if (data->actual)
	{
		data->actual = data->actual->previous;
		data->cursor = get_char_pos(data, data->actual);
		teleport_cursor(data->cursor);
	}
}

void	on_press_right_arrow_key(t_readline *data)
{
	if (!data->actual && data->first)
	{
		data->actual = data->first;
		data->cursor = get_char_pos(data, data->actual);
		teleport_cursor(data->cursor);
	}
	else if (data->actual && data->actual->next)
	{
		data->actual = data->actual->next;
		data->cursor = get_char_pos(data, data->actual);
		teleport_cursor(data->cursor);
	}
}

void	on_press_home_key(t_readline *data)
{
	data->actual = NULL;
	data->cursor = get_char_pos(data, data->actual);
	teleport_cursor(data->cursor);
}

void	on_press_end_key(t_readline *data)
{
	data->actual = last_char(data->first);
	data->cursor = get_char_pos(data, data->actual);
	teleport_cursor(data->cursor);
}

void	on_press_breakline_key(t_readline *data)
{
	char	*build;

	build = build_result(*data, 0);
	if (get_open_quote(build) == 0)
	{
		on_press_end_key(data);
		if (data->cursor.y != get_terminal_size(data, 0).y)
		{
			write(0, "\n", 1);
			data->cursor.y++;
		}
		data->cursor.x = 0;
		teleport_cursor(data->cursor);
		return ;
	}
	process_default_key(data, '\n');
	on_write(data);
}
