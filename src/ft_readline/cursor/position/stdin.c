/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:27:37 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/09 17:20:12 by lroussel         ###   ########.fr       */
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
	if (!ft_isdigit(input[i]))
		return (0);
	while (ft_isdigit(input[i]))
		*row = (*row * 10) + (input[i++] - '0');
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (!ft_isdigit(input[i]))
		return (0);
	while (ft_isdigit(input[i]))
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
	while (i < n && ft_isdigit(input[i]))
		*row = (*row) * 10 + (input[i++] - '0');
	while (i < n && (input[i] == ' ' || input[i] == '\t'))
		i++;
	while (i < n && ft_isdigit(input[i]))
		*col = (*col) * 10 + (input[i++] - '0');
	return ((*row) > 0 && (*col) > 0);
}
