/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:29:07 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/24 15:00:42 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	fix_coordinate(int *coordinate, int max)
{
	if (*coordinate < 1)
		*coordinate = 1;
	else if (*coordinate > max)
		*coordinate = max;
}

void	move_cursor(t_vector2 *cursor, int gap)
{
	t_vector2	size;
	int			s;
	int			v;

	if (gap == 0)
		return ;
	size = get_terminal_size();
	v = ft_abs(gap);
	s = 1 - 2 * (gap < 0);
	while (v-- > 0)
	{
		cursor->x += s;
		if (cursor->x < 1 || cursor->x > size.x)
		{
			cursor->y += s;
			if (cursor->y < 1 || cursor->y > size.y)
			{
				fix_coordinate(&cursor->y, size.y);
				cursor->x -= s;
				break ;
			}
			fix_coordinate(&cursor->x, size.x);
		}
	}
	teleport_cursor(*cursor);
}

void	move_x(t_vector2 *cursor, int gap)
{
	t_vector2	size;
	int			s;
	int			v;

	if (gap == 0)
		return ;
	size = get_terminal_size();
	v = ft_abs(gap);
	s = 1 - 2 * (gap < 0);
	while (v > 0)
	{
		v--;
		cursor->x += s;
		if (cursor->x <= 0 || cursor->x >= size.x)
			break ;
	}
	teleport_cursor(*cursor);
}

void	move_y(t_vector2 *cursor, int gap)
{
	t_vector2	size;
	int			s;
	int			v;

	if (gap == 0)
		return ;
	size = get_terminal_size();
	v = ft_abs(gap);
	s = 1 - 2 * (gap < 0);
	while (v > 0)
	{
		v--;
		cursor->y += s;
		if (cursor->y <= 0 || cursor->y >= size.y)
			break ;
	}
	teleport_cursor(*cursor);
}

void	teleport_cursor(t_vector2 pos)
{
	ft_putstr_fd("\033[", 1);
	ft_putnbr_fd(pos.y, 1);
	ft_putchar_fd(';', 1);
	ft_putnbr_fd(pos.x, 1);
	ft_putchar_fd('H', 1);
}
