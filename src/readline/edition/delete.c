/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:46:45 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/25 15:00:25 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	on_delete(t_readline *data)
{
	char		*build;
	t_vector2	size;

	hide_cursor();
	build = build_result(*data, last_char(data->first));
	size = get_terminal_size(data, 1);
	update_position(data, size, build);
	teleport_cursor(data->pos);
	print_build(build);
	write(0, " ", 1);
	free(build);
	clear_next_line(data, size);
	if (data->actual && data->actual->next)
		data->cursor = get_char_pos(data, data->actual);
	else
		data->cursor = get_char_pos(data, NULL);
	teleport_cursor(data->cursor);
	show_cursor();
}
