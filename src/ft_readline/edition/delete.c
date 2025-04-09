/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:46:45 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/09 14:31:20 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void	clear_next_lines(t_readline_data *data)
{
	if (!data->current)
	{
		data->current = data->first;
		teleport_cursor(get_char_pos(data, last_char(data->current)));
		data->current = NULL;
	}
	else
		teleport_cursor(get_char_pos(data, last_char(data->current)));
	write(get_extra_data_in_fd(), CLEAR_TERMINAL_AFTER_CURSOR, 4);
	teleport_cursor(data->cursor);
}

void	on_delete(t_readline_data *data)
{
	char		*build;

	get_terminal_size(data, 1);
	hide_cursor();
	if (data->current)
		build = list_to_string(*data, last_char(data->current));
	else
		build = list_to_string(*data, last_char(data->first));
	teleport_cursor(data->pos);
	print_build(build);
	write(0, " ", 1);
	clear_next_lines(data);
	free(build);
	if (data->current && data->current->next)
		data->cursor = get_char_pos(data, data->current);
	else
		data->cursor = get_char_pos(data, NULL);
	teleport_cursor(data->cursor);
	show_cursor();
}
