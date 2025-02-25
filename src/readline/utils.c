/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:11:11 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/25 14:46:39 by lroussel         ###   ########.fr       */
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

char	get_open_quote(const char *stashed)
{
	int		i;
	char	cur_quote;
	char	back_slashed;

	i = 0;
	cur_quote = 0;
	back_slashed = 0;
	while (stashed[i])
	{
		if (stashed[i] == '\\' && !back_slashed)
			back_slashed = 1;
		else if ((stashed[i] == '\'' || stashed[i] == '\"') && !back_slashed)
		{
			if (cur_quote == stashed[i])
				cur_quote = 0;
			else if (cur_quote == 0)
				cur_quote = stashed[i];
		}
		else
			back_slashed = 0;
		i++;
	}
	return (cur_quote);
}

void	fix_cursor(t_readline *data, t_vector2 size)
{
	static t_vector2	old_size = {0, 0};
	t_vector2			old_cursor;
	int					diff;

	if (old_size.y == 0)
		old_size = size;
	if ((size.x != old_size.x || size.y != old_size.y))
	{
		old_cursor = data->cursor;
		get_cursor_position(&data->cursor);
		if (data->pos.x != 0)
		{
			diff = (((3 + ft_strlen(build_result(*data))) / old_size.x)
					- ((3 + ft_strlen(build_result(*data))) / size.x));
			data->initial_pos.y -= old_cursor.y - data->cursor.y - diff;
			if (old_size.y < size.y)
				data->initial_pos.y -= diff;
		}
		old_size = size;
		data->pos.y = data->initial_pos.y;
	}
}

t_vector2	get_terminal_size(t_readline *data)
{
	struct winsize	w;
	t_vector2		size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	size.x = w.ws_col;
	size.y = w.ws_row;
	fix_cursor(data, size);
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
