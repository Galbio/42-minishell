/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:24 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/09 15:25:55 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	on_write(t_readline_data *data)
{
	char		*build;
	t_vector2	size;

	hide_cursor();
	build = list_to_string(*data, 0);
	teleport_cursor(data->pos);
	print_build(build);
	size = get_terminal_size(data, 1);
	update_position(data, size, build);
	free(build);
	data->cursor = get_char_pos(data, data->current);
	teleport_cursor(data->cursor);
	show_cursor();
}
