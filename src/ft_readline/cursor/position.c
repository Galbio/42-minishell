/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:45:00 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 11:21:32 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

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

void	read_cursor_response(int tty, char *buf)
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

int	parse_row_col_from_plain_text(const char *input, int *row, int *col)
{
	int	i;

	i = 0;
	*row = 0;
	*col = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (!(input[i] >= '0' && input[i] <= '9'))
		return (0);
	while (input[i] >= '0' && input[i] <= '9')
		*row = (*row * 10) + (input[i++] - '0');
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (!(input[i] >= '0' && input[i] <= '9'))
		return (0);
	while (input[i] >= '0' && input[i] <= '9')
		*col = (*col * 10) + (input[i++] - '0');
	return (1);
}

int	get_cursor_position_from_stdin(int *row, int *col)
{
	int		n;
	int		i;
	char	input[32];

	n = read(STDIN_FILENO, input, sizeof(input) - 1);
	if (n <= 0)
		return (0);
	input[n] = '\0';
	if (parse_cursor_response(input, row, col)
		|| parse_row_col_from_plain_text(input, row, col))
		return (1);
	i = 0;
	while (i < n && input[i] == ' ')
		i++;
	while (i < n && input[i] >= '0' && input[i] <= '9')
		*row = (*row) * 10 + (input[i++] - '0');
	while (i < n && (input[i] == ' ' || input[i] == '\t'))
		i++;
	while (i < n && input[i] >= '0' && input[i] <= '9')
		*col = (*col) * 10 + (input[i++] - '0');
	if ((*row) > 0 && (*col) > 0)
		return (1);
	return (0);
}

int	get_cursor_position(t_vector2 *pos)
{
	if (isatty(STDIN_FILENO) && get_cursor_position_from_tty(&pos->y, &pos->x))
		return (1);
	return (get_cursor_position_from_stdin(&pos->y, &pos->x));
}
