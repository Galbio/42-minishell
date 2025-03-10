/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:22:14 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/10 10:20:12 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	on_resize(t_readline *data, t_vector2 new)
{
	t_char	*last = last_char(data->first);
	get_cursor_position(&data->cursor);
	data->pos.y = data->cursor.y - count_low_newlines(data, last) - count_hard_newlines(*data, last);
	if (data->pos.y < 1)
		data->pos.y = 1;
	data->cursor = get_char_pos(data, last);
	teleport_cursor(data->cursor);
	data->old_tsize = new;
}
