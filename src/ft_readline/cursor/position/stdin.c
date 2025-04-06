/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:27:37 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 13:29:49 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static int	parse_row_col_from_plain_text(const char *input, int *row, int *col)
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
