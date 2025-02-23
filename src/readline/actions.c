/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:11:06 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/23 20:11:06 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	delete_character(t_readline *data)
{
	t_char	*c;

	c = data->actual;
	remove_char(&data->actual);
	if (data->actual != c)
		data->size--;
	if (!data->actual && data->size == 0)
		data->first = NULL;
	write(1, "\033[D", 3);
}

static void	move_cursor_left(t_readline *data)
{
	data->update = 1;
	if (data->actual)
	{
		write(1, "\033[D", 3);
		data->actual = data->actual->previous;
	}
}

static void	move_cursor_right(t_readline *data)
{
	data->update = 1;
	if (!data->actual && data->first)
	{
		data->actual = data->first;
		write(1, "\033[C", 3);
	}
	else if (data->actual && data->actual->next)
	{
		write(1, "\033[C", 3);
		data->actual = data->actual->next;
	}
}

int	process_special_keys(t_readline *data)
{
	if ((data->c == 127) && data->size > 0)
	{
		delete_character(data);
		return (1);
	}
	if (data->c == 4479771)
	{
		move_cursor_left(data);
		return (1);
	}
	if (data->c == 4414235)
	{
		move_cursor_right(data);
		return (1);
	}
	return (0);
}

void	handle_key_input(t_readline *data, char buffer[100])
{
	if (!process_special_keys(data))
	{
		if (!data->first)
		{
			data->first = new_char(*((int *)buffer));
			data->actual = data->first;
		}
		else
		{
			if (!data->actual && data->first)
			{
				add_char_front(&data->first, new_char(*((int *)buffer)));
				write(1, "\033[C", 3);
			}
			else
			{
				add_char_after(&data->actual, new_char(*((int *)buffer)));
				data->actual = data->actual->next;
			}
		}
		data->size++;
	}
}
