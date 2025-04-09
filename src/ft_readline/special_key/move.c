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

#include "ft_readline.h"

void	move_left_key(t_readline_data *data)
{
	if (data->current)
	{
		data->current = data->current->previous;
		data->cursor = get_char_pos(data, data->current);
		teleport_cursor(data->cursor);
		get_readline_struct()->cat_stash = 0;
	}
}

void	move_right_key(t_readline_data *data)
{
	if (!data->current && data->first)
	{
		data->current = data->first;
		data->cursor = get_char_pos(data, data->current);
		teleport_cursor(data->cursor);
		get_readline_struct()->cat_stash = 0;
	}
	else if (data->current && data->current->next)
	{
		data->current = data->current->next;
		data->cursor = get_char_pos(data, data->current);
		teleport_cursor(data->cursor);
		get_readline_struct()->cat_stash = 0;
	}
}
