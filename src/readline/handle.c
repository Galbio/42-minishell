/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:45:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/12 13:37:07 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	process_default_key(t_readline *data, char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (!data->first)
		{
			data->first = new_char(buffer[i]);
			data->actual = data->first;
		}
		else
		{
			if (!data->actual && data->first)
			{
				add_char_front(&data->first, new_char(buffer[i]));
				data->actual = data->first;
				write(1, "\033[C", 3);
			}
			else
			{
				add_char_after(&data->actual, new_char(buffer[i]));
				data->actual = data->actual->next;
			}
		}
		i++;
	}
	data->size += i;
}

int	handle_special_keys(t_readline *data, char *buffer)
{
	t_special_key	*key;

	//printf("\n\n%i %i %i %i\n", buffer[0], buffer[1], buffer[2], buffer[3]);
	key = get_by_sequence(buffer);
	if (key)
		return (!(key->callback)(data));
	return (!ft_isprint(buffer[0]) && buffer[1]);
}

void	handle_key_input(t_readline *data, char *buffer)
{
	if (handle_special_keys(data, buffer))
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
