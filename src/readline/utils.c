/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:11:11 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/26 11:33:23 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int	count_newlines(t_char *c, t_char *actual, int *lc)
{
	int	bn_count;

	bn_count = 0;
	while (c && c != actual)
	{
		(*lc)++;
		if (c->c == '\n')
		{
			bn_count++;
			*lc = 0;
		}
		c = c->next;
	}
	return (bn_count);
}

void	init_terminal_size(t_vector2 *size)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	size->x = w.ws_col;
	size->y = w.ws_row;
}

t_vector2	get_terminal_size(t_readline *data)
{
	struct winsize	w;
	t_vector2		size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	size.x = w.ws_col;
	size.y = w.ws_row;
	check_resize(data, size);
	return (size);
}

int	count_total_newlines(const char *prompt, t_readline data)
{
	int		i;
	int		count;
	t_char	*c;

	i = 0;
	count = 0;
	while (prompt[i])
		count += (prompt[i++] == '\n');
	c = data.first;
	while (c)
	{
		count += c->c == '\n';
		c = c->next;
	}
	return (count);
}
