/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:11:06 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/26 19:30:09 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	delete_character(t_readline *data)
{
	t_char	*c;

	if (!data->actual)
		return ;
	if (data->actual == data->first)
	{
		data->first = data->first->next;
		remove_char(&data->actual);
		data->actual = NULL;
		on_delete(data, 1);
		return ;
	}
	c = data->actual;
	remove_char(&data->actual);
	if (data->actual != c)
		data->size--;
	if (!data->actual && data->size == 0)
		data->first = NULL;
	on_delete(data, 1);
}

static void	move_cursor_left(t_readline *data)
{
	if (data->actual)
	{
		move_cursor(data, -1);
		data->actual = data->actual->previous;
	}
}

static void	move_cursor_right(t_readline *data)
{
	if (!data->actual && data->first)
	{
		data->actual = data->first;
		move_cursor(data, 1);
	}
	else if (data->actual && data->actual->next)
	{
		data->actual = data->actual->next;
		move_cursor(data, 1);
	}
}

int	process_special_keys(t_readline *data, char *buffer)
{
	if ((buffer[0] == 127) && data->size > 0)
	{
		delete_character(data);
		return (1);
	}
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 68)
	{
		move_cursor_left(data);
		return (1);
	}
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 67)
	{
		move_cursor_right(data);
		return (1);
	}
	return (!ft_isprint(buffer[0]));
}
