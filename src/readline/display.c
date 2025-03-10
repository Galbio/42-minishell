/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:24 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/10 10:48:15 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	fix_last_line(t_readline *data, t_vector2 size)
{
	t_char	*last;

	last = last_char(data->first);
	data->pos.y = size.y - count_low_newlines(data, last)
		- count_hard_newlines(*data, last);
}

static void	print_build(char *build)
{
	int	i;

	if (!build || !build[0])
	{
		write(1, "\033[K", 3);
		return ;
	}
	i = 0;
	while (i == 0 || (build[i - 1] && build[i - 1] != '\n'))
		i++;
	if (i > 1 && build[i - 1] == '\n')
	{
		write(1, build, i - 1);
		write(1, "\033[K\n", 4);
	}
	else if (i == 1 && build[i] == '\n')
		write(1, "\033[K\n", 4);
	else
		write(1, build, i);
	write(1, "\033[K", 3);
	if (i < (int)ft_strlen(build))
		print_build(build + i);
}

static void	update_position(t_readline *data, t_vector2 size,
		char *build, char *buffer)
{
	if (data->cursor.y == size.y)
	{
		if ((ft_strlen(data->prompt) + (int)ft_strlen(last_newline(build)))
			% size.x == 0)
		{
			write(1, "\n", 1);
			move_y(data, -1);
		}
		fix_last_line(data, size);
	}
	if (buffer[0] == '\n')
	{
		write(1, "\n", 1);
		move_y(data, -1);
	}
}

void	on_write(t_readline *data, char *buffer)
{
	char		*build;
	t_vector2	size;

	size = get_terminal_size(data, 1);
	build = build_result(*data, last_char(data->first));
	get_cursor_position(&data->cursor);
	update_position(data, size, build, buffer);
	teleport_cursor(data->pos);
	print_build(build);
	free(build);
	if (buffer[0] == '\n' && data->cursor.y != size.y)
	{
		data->cursor.x = 0;
		data->cursor.y += 1;
		teleport_cursor(data->cursor);
	}
	data->cursor = get_char_pos(data, data->actual);
	teleport_cursor(data->cursor);
}

void	on_delete(t_readline *data)
{
	char	*build;

	build = build_result(*data, last_char(data->first));
	teleport_cursor(data->pos);
	print_build(build);
	free(build);
	if (data->actual)
	{
		data->cursor = get_char_pos(data, last_char(data->first));
		if (data->cursor.y < 23)
		{
			move_y(data, 1);
			write(1, "\033[2K", 4);
		}
	}
	if (!data->actual || data->actual->next)
		data->cursor = get_char_pos(data, data->actual);
	else
		data->cursor = get_char_pos(data, NULL);
	write(1, " ", 1);
	teleport_cursor(data->cursor);
}
