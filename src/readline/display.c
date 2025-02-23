/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:24 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/23 20:12:50 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	clear_terminal(int count, int bn_count)
{
	int			width;
	int			l;
	int			extra;

	width = get_terminal_width();
	l = count / width - 1 * (count % width == 0) + bn_count;
	if ((count % width) == 1)
		write(1, "\n", 1);
	extra = width;
	while (extra-- > 0)
		write(1, "\033[D\033[P", 6);
	while (l-- > 0)
		write(1, "\033[A\033[D\033[P", 3);
}

void	update_cursor_position(const char *prompt, t_readline data)
{
	t_vector2	pos;
	int			i;

	i = get_terminal_width();
	pos = get_position(prompt, data);
	pos.y -= 1;
	while (i-- > 0)
		write(1, "\033[D", 3);
	while (pos.x-- > 0)
		write(1, "\033[C", 3);
	while (pos.y-- > 0)
		write(1, "\033[B", 3);
}

void	update_terminal(t_readline	*data, const char *prompt)
{
	if (!data->update)
		return ;
	clear_terminal(data->size + ft_strlen(prompt),
		count_total_newlines(prompt, *data));
	write(1, prompt, ft_strlen(prompt));
	ft_putstr_fd(build_result(*data), 1);
	update_cursor_position(prompt, *data);
}

static int	calculate_y(const char *prompt, t_readline data,
	int i, int bn_count)
{
	int	width;
	int	size;

	width = get_terminal_width();
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
	v.x = lc % get_terminal_width();
	v.y = calculate_y(prompt, data, i, bn_count);
	return (v);
}
