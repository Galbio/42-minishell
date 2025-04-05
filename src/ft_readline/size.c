/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:22:14 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/11 12:34:22 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	init_terminal_size(t_vector2 *size)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	size->x = w.ws_col;
	size->y = w.ws_row;
}

static void	on_resize(t_readline *data)
{
	get_cursor_position(&data->cursor);
	data->pos.y = data->cursor.y - count_low_newlines(data, data->actual)
		- count_hard_newlines(*data, data->actual);
	if (data->pos.y < 1)
		data->pos.y = 1;
	data->cursor = get_char_pos(data, data->actual);
	teleport_cursor(data->cursor);
}

t_vector2	get_terminal_size(t_readline *data, int check_resize)
{
	struct winsize	w;
	t_vector2		size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	size.x = w.ws_col;
	size.y = w.ws_row;
	if (check_resize
		&& ((size.x != data->old_tsize.x) || size.y != (data->old_tsize.y)))
	{
		on_resize(data);
		data->old_tsize = size;
	}
	return (size);
}
