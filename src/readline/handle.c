/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:45:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/14 13:02:24 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	process_default_key(t_readline *data, char key)
{
	if (!data->first)
	{
		data->first = new_char(key);
		data->actual = data->first;
	}
	else
	{
		if (!data->actual && data->first)
		{
			add_char_front(&data->first, new_char(key));
			data->actual = data->first;
			write(1, "\033[C", 3);
		}
		else
		{
			add_char_after(&data->actual, new_char(key));
			data->actual = data->actual->next;
		}
	}
	data->size += 1;
}

int	handle_special_keys(t_readline *data, char *buffer)
{
	t_special_key	*key;

	key = get_by_sequence(buffer);
	if (key)
	{
		get_terminal_size(data, 1);
		(key->callback)(data);
		return (ft_strlen(key->sequence));
	}
	return (0);
}

int	handle_key_input(t_readline *data, char *buffer)
{
	int	res;

	res = handle_special_keys(data, buffer);
	if (res > 0)
	{
		data->update = 0;
		return (res);
	}
	if (buffer[0] == '\n')
	{
		get_cursor_position(&data->cursor);
		data->cursor.x = 0;
	}
	process_default_key(data, buffer[0]);
	return (1);
}
