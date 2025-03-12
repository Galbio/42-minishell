/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:11:06 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/12 10:20:43 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int	on_press_delete_key(t_readline *data)
{
	t_char	*c;

	if (!data->actual)
		return (0);
	if (data->actual == data->first)
	{
		data->first = data->first->next;
		remove_char(&data->actual);
		data->actual = NULL;
		on_delete(data);
		return (0);
	}
	c = data->actual;
	remove_char(&data->actual);
	if (data->actual != c)
		data->size--;
	if (!data->actual && data->size == 0)
		data->first = NULL;
	on_delete(data);
	return (0);
}

int	on_press_left_arrow_key(t_readline *data)
{
	get_terminal_size(data, 1);
	if (data->actual)
	{
		data->actual = data->actual->previous;
		data->cursor = get_char_pos(data, data->actual);
		teleport_cursor(data->cursor);
	}
	return (0);
}

int	on_press_right_arrow_key(t_readline *data)
{
	get_terminal_size(data, 1);
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
	return (0);
}

int	on_press_home_key(t_readline *data)
{
	get_terminal_size(data, 1);
	data->actual = data->first;
	data->cursor = get_char_pos(data, data->actual);
	teleport_cursor(data->cursor);
	return (0);
}
int	on_press_end_key(t_readline *data)
{
	get_terminal_size(data, 1);
	data->actual = last_char(data->first);
	data->cursor = get_char_pos(data, data->actual);
	teleport_cursor(data->cursor);
	return (0);
}
