/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:46:45 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/05 22:01:49 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void	clear_next_line(t_readline_data *data, t_vector2 size)
{
	int	first;

	first = 0;
	if (!data->current)
	{
		data->current = data->first;
		first = 1;
	}
	data->cursor = get_char_pos(data, last_char(data->first));
	if (data->cursor.y < size.y - 1)
	{
		move_y(data, 1);
		write(get_extra_data_in_fd(), "\033[2K", 4);
	}
	if (first)
		data->current = NULL;
}

void	on_delete(t_readline_data *data)
{
	char		*build;
	t_vector2	size;

	hide_cursor();
	build = list_to_string(*data, last_char(data->first));
	size = get_terminal_size(data, 1);
	update_position(data, size, build);
	teleport_cursor(data->pos);
	print_build(build);
	write(0, " ", 1);
	free(build);
	clear_next_line(data, size);
	if (data->current && data->current->next)
		data->cursor = get_char_pos(data, data->current);
	else
		data->cursor = get_char_pos(data, NULL);
	teleport_cursor(data->cursor);
	show_cursor();
}
