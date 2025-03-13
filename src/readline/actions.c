/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:11:06 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/13 17:38:17 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int	delete_char(t_readline *data)
{
	t_char	*c;

	if (!data->actual || data->size <= 0)
		return (1);
	if (data->actual == data->first)
	{
		data->first = data->first->next;
		remove_char(&data->actual);
		data->actual = NULL;
		on_delete(data);
		return (1);
	}
	c = data->actual;
	remove_char(&data->actual);
	if (data->actual != c)
		data->size--;
	if (!data->actual && data->size == 0)
		data->first = NULL;
	on_delete(data);
	return (1);
}

int	move_cursor_left(t_readline *data)
{
	get_terminal_size(data, 1);
	if (data->actual)
	{
		data->actual = data->actual->previous;
		data->cursor = get_char_pos(data, data->actual);
		teleport_cursor(data->cursor);
	}
	return (1);
}

int	move_cursor_right(t_readline *data)
{
	get_terminal_size(data, 1);
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
	return (1);
}

int	ctrl_c(t_readline *data)
{
	data->cursor = get_char_pos(data, last_char(data->first));
	teleport_cursor(data->cursor);
	disable_raw_mode();
	write(0, "^C\n", 3);
	enable_raw_mode();
	data->exit = 1;
	if (ft_readline_must_exit())
	{
		free_ft_readline(data);
		disable_raw_mode();
		exit(0);
	}
	return (1);
}

//TODO: when data->actual->next
int	ctrl_d(t_readline *data)
{
	if (data->first == NULL)
	{
		disable_raw_mode();
		free_ft_readline(data);
		write(0, "\nexit\n", 6);
		exit(0);
	}
	return (1);
}
