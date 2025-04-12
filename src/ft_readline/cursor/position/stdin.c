/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:27:37 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/12 19:51:08 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void	set_tcsamow(struct termios *old_term)
{
	struct termios	new_term;

	tcgetattr(STDIN_FILENO, old_term);
	new_term = *old_term;
	new_term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

static int	read_terminal_response(char *buffer, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size - 1)
	{
		if (read(STDIN_FILENO, &buffer[i], 1) != 1)
			break ;
		if (buffer[i] == 'R')
			break ;
		i++;
	}
	buffer[i] = '\0';
	return ((!(buffer[0] == '\033' && buffer[1] == '[')) * -1);
}

static int	parse_cursor_position(const char *response, int *rows, int *cols)
{
	const char	*ptr;

	ptr = response + 2;
	*rows = 0;
	while (ft_isdigit(*ptr))
	{
		*rows = *rows * 10 + (*ptr - '0');
		ptr++;
	}
	if (*ptr++ != ';')
		return (-1);
	*cols = 0;
	while (ft_isdigit(*ptr))
	{
		*cols = *cols * 10 + (*ptr - '0');
		ptr++;
	}
	return ((*ptr != 'R') * -1);
}

int	get_cursor_position_from_stdin(int *row, int *col)
{
	struct termios	old_term;
	char			response[32];
	int				status;

	set_tcsamow(&old_term);
	write(STDOUT_FILENO, DISPLAY_CURSOR_POSITION, 4);
	status = read_terminal_response(response, sizeof(response));
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
	if (status == -1)
		return (-1);
	return (parse_cursor_position(response, row, col));
}
