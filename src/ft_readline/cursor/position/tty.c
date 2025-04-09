/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:24:52 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 13:30:27 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void	read_cursor_response(int tty, char *buf)
{
	int		i;
	char	ch;

	i = 0;
	while (i < (int)(sizeof(buf) - 1))
	{
		if (read(tty, &ch, 1) != 1)
			break ;
		buf[i++] = ch;
		if (ch == 'R')
			break ;
	}
	buf[i] = '\0';
}

int	get_cursor_position_from_tty(int *row, int *col)
{
	struct termios	oldt;
	struct termios	newt;
	int				tty;
	char			buf[32];

	tty = open("/dev/tty", O_RDWR);
	if (tty < 0)
		return (0);
	if (tcgetattr(tty, &oldt) == -1)
		return (0);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(tty, TCSANOW, &newt) == -1)
		return (0);
	write(tty, "\033[6n", 4);
	read_cursor_response(tty, buf);
	tcsetattr(tty, TCSANOW, &oldt);
	close(tty);
	return (parse_cursor_response(buf, row, col));
}
