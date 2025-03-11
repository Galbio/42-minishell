/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:11:06 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/11 12:03:30 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int	delete_char(t_readline *data)
{
	t_char	*c;

	if (!data->actual)
		return (1);
	if (data->actual == data->first)
	{
		data->first = data->first->next;
		remove_char(&data->actual);
		data->actual = NULL;
		on_delete(data, 1);
		return (1);
	}
	c = data->actual;
	remove_char(&data->actual);
	if (data->actual != c)
		data->size--;
	if (!data->actual && data->size == 0)
		data->first = NULL;
	on_delete(data, 1);
	return (1);
}

int	move_cursor_left(t_readline *data)
{
	if (data->actual)
	{
		move_cursor(data, -1);
		data->actual = data->actual->previous;
	}
	return (1);
}

int	move_cursor_right(t_readline *data)
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
	return (1);
}

int	ctrl_c(t_readline *data)
{
	write(1, "^C\n", 3);
	data->exit = 1;
	if (ft_readline_must_exit())
	{
		free_ft_readline(data);
		disable_raw_mode();
		exit(0);
	}
	return (1);
}

void	ctrl_d(t_readline *data)
{
	disable_raw_mode();
	free_ft_readline(data);
	write(1, "\n", 1);
	exit(0);
}
