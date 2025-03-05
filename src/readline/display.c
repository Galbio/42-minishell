/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:24 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/05 10:35:25 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	update_position(t_readline *data, char *build)
{
	t_vector2	size;
	int			prompt_len;

	size = get_terminal_size(data);
	prompt_len = ft_strlen(data->prompt);
	data->pos.y = data->initial_pos.y
		- (((prompt_len + ft_strlen(build)) / size.x) + count_hard_newlines(*data, 0));
	if (data->initial_pos.y != size.y)
		data->pos.y += size.y - data->initial_pos.y;
	if (data->pos.y != data->initial_pos.y)
		data->pos.x = prompt_len + 1;
}

void	print_build(char *build)
{
	int	i;

	if (!build || !build[0])
		return ;
	i = 0;
	while (i == 0 || (build[i - 1] && build[i - 1] != '\n'))
		i++;
	if (i > 1 && build[i - 1] == '\n')
	{
		write(1, build, i - 1);
		write(1, "\033[K", 3);
		write(1, "\n", 1);
		write(1, "\033[K", 3);
	}
	else if (i == 1 && build[i] == '\n')
	{
		write(1, "\033[K", 3);
		write(1, "\n", 1);
		write(1, "\033[K", 3);
	}
	else
	{
		write(1, build, i);
		write(1, "\033[K", 3);
	}
	if (i < (int)ft_strlen(build))
		print_build(build + i);
}

void	on_write(t_readline *data, char *buffer)
{
	char		*build;

	if (!data->update)
		return ;
	get_terminal_size(data);
	build = build_result(*data, 0);
	get_cursor_position(&data->cursor);
	if (data->cursor.y == get_terminal_size(data).y)
	{
		if ((ft_strlen(data->prompt)
				+ (int)ft_strlen(build)) % get_terminal_size(data).x == 0)
		{
			write(1, "\n", 1);
			move_y(data, -1);
		}
		update_position(data, build);
	}
	if (buffer[0] == '\n')
	{
		write(1, "\n", 1);
		move_y(data, -1);
	}
	teleport_cursor(data->pos);
	print_build(build);
	ft_putstr_fd("\033[K", 1);
	free(build);
	if (buffer[0] == '\n' && data->cursor.y != get_terminal_size(data).y)
	{
		data->cursor.x = 0;
		data->cursor.y += 1;
		teleport_cursor(data->cursor);
	}
	data->cursor = actual_char_pos(data);
	teleport_cursor(data->cursor);
}

char	*last_newline(char *build)
{
	char	*newline;
	int		i;

	newline = build;
	i = 0;
	while (build[i])
	{
		if (build[i] == '\n')
			newline = build + i + 1;
		i++;
	}
	return (newline);
}

t_vector2	last_char_pos(t_readline *data)
{
	t_vector2	size;
	int			prompt_len;
	int			len;
	int			line_len;
	char		*build;
	t_vector2	v;

	build = build_result(*data, 0);
	size = get_terminal_size(data);
	prompt_len = ft_strlen(data->prompt);
	len = ft_strlen(build) + prompt_len;
	line_len = ft_strlen(last_newline(build));
	if (line_len == (int)ft_strlen(build))
		line_len += prompt_len;
	v.x = ((line_len % size.x)) + 1;
	v.y = data->initial_pos.y + ((len / size.x)) + count_hard_newlines(*data, 1);
	return (v);
}

t_vector2	actual_char_pos(t_readline *data)
{
	t_vector2	size;
	int			prompt_len;
	int			len;
	int			line_len;
	char		*build;
	t_vector2	v;

	build = build_result(*data, 1);
	size = get_terminal_size(data);
	prompt_len = ft_strlen(data->prompt);
	len = ft_strlen(build) + prompt_len;
	line_len = ft_strlen(last_newline(build));
	if (line_len == (int)ft_strlen(build))
		line_len += prompt_len;
	v.x = ((line_len % size.x)) + 1;
	v.y = data->initial_pos.y + ((len / size.x)) + count_hard_newlines(*data, 1);
	return (v);
}

void	on_delete(t_readline *data, int deleted)
{
	char	*build;

	(void)(deleted);
	build = build_result(*data, 0);
	teleport_cursor((t_vector2){0, last_char_pos(data).y + 2});
	write(1, "\033[K", 4);
	teleport_cursor(data->pos);
	print_build(build);
	free(build);
	data->cursor = actual_char_pos(data);
	teleport_cursor(data->cursor);
	write(1, "\033[K", 4);
}
