/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:20:00 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/14 14:20:32 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

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
