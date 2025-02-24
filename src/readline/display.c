/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:24 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/24 15:02:17 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	on_write(t_readline *data)
{
	char	*build;

	if (!data->update)
		return ;
	teleport_cursor(data->pos);
	build = build_result(*data);
	ft_putstr_fd(build, 1);
	free(build);
	move_cursor(&data->cursor, 1);
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
	move_cursor(&data->cursor, -deleted);
}

static int	calculate_y(const char *prompt, t_readline data,
	int i, int bn_count)
{
	int	width;
	int	size;

	width = get_terminal_size().x;
	size = data.size;
	return ((size / width - 1 * (size % width == 0)
			+ count_total_newlines(prompt, data))
		- (i / width - 1 * (i % width == 0) + bn_count));
}

t_vector2	get_position(const char *prompt, t_readline data)
{
	t_vector2	v;
	t_char		*c;
	int			i;
	int			lc;
	int			bn_count;

	i = 0;
	lc = ft_strlen(prompt);
	c = data.first;
	bn_count = count_newlines(c, data.actual, &lc);
	if (data.actual && data.actual->c == '\n')
	{
		bn_count++;
		lc = 0;
	}
	else if (data.actual)
		lc++;
	else if (data.first)
		lc = ft_strlen(prompt);
	v.x = lc % get_terminal_size().x;
	v.y = calculate_y(prompt, data, i, bn_count);
	return (v);
}
