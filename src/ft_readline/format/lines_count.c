/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:22:28 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/12 19:36:20 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	count_low_newlines(t_readline_data *data, t_readline_char *to)
{
	t_vector2			size;
	int					j;
	int					count;
	t_readline_char		*c;

	size = get_terminal_size(data, 0);
	j = ((ft_strlen_utf8_without_ansi(ft_getlast_newline((char *)data->prompt))
				* data->display_prompt) % size.x) + data->offset;
	count = 0;
	if ((to && !data->current) || (data->first && !data->current))
		return (count);
	c = data->first;
	while (c && (to == NULL || c != to->next))
	{
		j++;
		if (c->sequence[0] == '\n' || (j >= size.x))
		{
			count += j / size.x
				- (c->sequence[0] == '\n' * (j % size.x == 1)
					* (!c->previous || c->previous->sequence[0] != '\n'));
			j = 0;
		}
		c = c->next;
	}
	return (count);
}

int	count_hard_newlines(t_readline_data data, t_readline_char *to)
{
	int				count;
	t_readline_char	*c;

	count = 0;
	c = data.first;
	if ((to && !data.current) || (data.first && !data.current))
		return (count);
	while (c && (to == NULL || c != to->next))
	{
		count += c->sequence[0] == '\n';
		c = c->next;
	}
	return (count);
}
