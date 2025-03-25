/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:24 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/25 14:46:39 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	on_write(t_readline *data)
{
	char		*build;
	t_vector2	size;

	hide_cursor();
	build = build_result(*data, 0);
	size = get_terminal_size(data, 1);
	update_position(data, size, build);
	teleport_cursor(data->pos);
	print_build(build);
	free(build);
	data->cursor = get_char_pos(data, data->actual);
	teleport_cursor(data->cursor);
	show_cursor();
}
