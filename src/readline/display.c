/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:24 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/25 11:59:59 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	update_position(t_readline *data, char *build)
{
	t_vector2	size;

	size = get_terminal_size(data);
	data->pos.y = data->initial_pos.y - ((3 + ft_strlen(build)) / size.x);
	if (data->initial_pos.y != size.y)
		data->pos.y += size.y - data->initial_pos.y;
	if (data->pos.y != data->initial_pos.y)
		data->pos.x = 4;
}

void	on_write(t_readline *data)
{
	char		*build;

	if (!data->update)
		return ;
	get_terminal_size(data);
	build = build_result(*data);
	if (data->cursor.y == get_terminal_size(data).y)
	{
		if ((3 + (int)ft_strlen(build)) % get_terminal_size(data).x == 0)
		{
			printf("\n");
			move_y(data, -1);
		}
		update_position(data, build);
	}
	teleport_cursor(data->pos);
	ft_putstr_fd(build, 1);
	ft_putstr_fd("\033[K", 1);
	free(build);
	move_cursor(data, 1);
}

void	on_delete(t_readline *data, int deleted)
{
	char	*build;
	int		spaces;

	build = build_result(*data);
	teleport_cursor(data->pos);
	ft_putstr_fd(build, 1);
	spaces = deleted;
	while (spaces-- > 0)
		ft_putchar_fd(' ', 1);
	free(build);
	move_cursor(data, -deleted);
}

static int	calculate_y(const char *prompt, t_readline *data,
	int i, int bn_count)
{
	int	width;
	int	size;

	width = get_terminal_size(data).x;
	size = data->size;
	return ((size / width - 1 * (size % width == 0)
			+ count_total_newlines(prompt, *data))
		- (i / width - 1 * (i % width == 0) + bn_count));
}

t_vector2	get_position(const char *prompt, t_readline *data)
{
	t_vector2	v;
	t_char		*c;
	int			i;
	int			lc;
	int			bn_count;

	i = 0;
	lc = ft_strlen(prompt);
	c = data->first;
	bn_count = count_newlines(c, data->actual, &lc);
	if (data->actual && data->actual->c == '\n')
	{
		bn_count++;
		lc = 0;
	}
	else if (data->actual)
		lc++;
	else if (data->first)
		lc = ft_strlen(prompt);
	v.x = lc % get_terminal_size(data).x;
	v.y = calculate_y(prompt, data, i, bn_count);
	return (v);
}
