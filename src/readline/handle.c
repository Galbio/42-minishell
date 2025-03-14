/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:45:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/13 17:37:58 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	process_default_key(t_readline *data, char *buffer)
{
	data->update = !process_special_keys(data, buffer);
	if (!data->update)
		return ;
	if (!data->first)
	{
		data->first = new_char(buffer[0]);
		data->actual = data->first;
	}
	else if (!data->actual && data->first)
	{
		add_char_front(&data->first, new_char(buffer[0]));
		data->actual = data->first;
		write(0, "\033[C", 3);
	}
	else
	{
		add_char_after(&data->actual, new_char(buffer[0]));
		data->actual = data->actual->next;
	}
	data->size++;
}

void	handle_key_input(t_readline *data, char *buffer)
{
	if (process_special_keys(data, buffer))
	{
		data->update = 0;
		return ;
	}
	if (buffer[0] == '\n')
	{
		get_cursor_position(&data->cursor);
		data->cursor.x = 0;
	}
	process_default_key(data, buffer);
}
