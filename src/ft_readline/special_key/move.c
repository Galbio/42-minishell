/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:20:00 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/24 10:16:58 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	move_left_key(t_readline *data)
{
	if (data->actual)
	{
		data->actual = data->actual->previous;
		data->cursor = get_char_pos(data, data->actual);
		teleport_cursor(data->cursor);
		get_readline_core()->cat_stash = 0;
	}
}

void	move_right_key(t_readline *data)
{
	if (!data->actual && data->first)
	{
		data->actual = data->first;
		data->cursor = get_char_pos(data, data->actual);
		teleport_cursor(data->cursor);
		get_readline_core()->cat_stash = 0;
	}
	else if (data->actual && data->actual->next)
	{
		data->actual = data->actual->next;
		data->cursor = get_char_pos(data, data->actual);
		teleport_cursor(data->cursor);
		get_readline_core()->cat_stash = 0;
	}
}
