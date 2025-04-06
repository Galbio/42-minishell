/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:45:00 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 13:30:48 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	parse_cursor_response(const char *buf, int *row, int *col)
{
	int	i;

	i = 0;
	*row = 0;
	*col = 0;
	if (buf[i] != '\033' || buf[i + 1] != '[')
		return (0);
	i += 2;
	while (buf[i] >= '0' && buf[i] <= '9')
	{
		*row = (*row * 10) + (buf[i] - '0');
		i++;
	}
	if (buf[i] != ';')
		return (0);
	i++;
	while (buf[i] >= '0' && buf[i] <= '9')
	{
		*col = (*col * 10) + (buf[i] - '0');
		i++;
	}
	if (buf[i] != 'R')
		return (0);
	return (1);
}

int	get_cursor_position(t_vector2 *pos)
{
	if (isatty(STDIN_FILENO) && get_cursor_position_from_tty(&pos->y, &pos->x))
		return (1);
	return (get_cursor_position_from_stdin(&pos->y, &pos->x));
}
