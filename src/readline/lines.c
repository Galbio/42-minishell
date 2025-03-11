/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:22:28 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/11 12:20:01 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static int	count_low_newlines_prompt(t_readline *data, int *j, t_vector2 size)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->prompt[i])
	{
		(*j)++;
		if (data->prompt[i] == '\n' || (*j >= size.x))
		{
			count += *j / size.x - (data->prompt[i] == '\n'
					* (*j % size.x == 1) * (data->prompt[i - 1] != '\n'));
			*j = 0;
		}
		i++;
	}
	return (count);
}

int	count_low_newlines(t_readline *data, t_char *to)
{
	int			j;
	t_vector2	size;
	int			count;
	t_char		*c;

	j = 0;
	size = get_terminal_size(data, 0);
	count = count_low_newlines_prompt(data, &j, size);
	if ((to && !data->actual) || (data->first && !data->actual))
		return (count);
	c = data->first;
	while (c && (to == NULL || c != to->next))
	{
		j++;
		if (c->c == '\n' || (j >= size.x))
		{
			count += j / size.x
				- (c->c == '\n' * (j % size.x == 1) * (c->previous->c != '\n'));
			j = 0;
		}
		c = c->next;
	}
	return (count);
}

int	count_hard_newlines(t_readline data, t_char *to)
{
	int		i;
	int		count;
	t_char	*c;

	i = 0;
	count = 0;
	while (data.prompt[i])
		count += (data.prompt[i++] == '\n');
	c = data.first;
	if ((to && !data.actual) || (data.first && !data.actual))
		return (count);
	while (c && (to == NULL || c != to->next))
	{
		count += c->c == '\n';
		c = c->next;
	}
	return (count);
}
