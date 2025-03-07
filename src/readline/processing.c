/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:30 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/07 16:22:54 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char	*build_result(t_readline data, t_char *to)
{
	char	*result;
	t_char	*c;
	int		i;
	int	len;

	if (!data.first || data.first->c == '\n')
		return (ft_strdup(""));
	len = data.size;
	if (to)
	{
		len = 1;
		c = to;
		while (c->previous)
		{
			len++;
			c = c->previous;
		}
	}
	else if (data.first && !data.actual)
		return (ft_strdup(""));
	result = malloc(sizeof(char) * (len + 1));
	c = data.first;
	i = 0;
	while (c && (!to || c != to->next))
	{
		result[i] = c->c;
		i++;
		c = c->next;
	}
	result[i] = '\0';
	return (result);
}

int	process_input(t_readline *data, char *buffer)
{
	char		*build;

	build = build_result(*data, last_char(data->first));
	if (buffer[0] == '\n' && get_open_quote(build) == 0)
	{
		data->cursor = get_char_pos(data, last_char(data->first));
		teleport_cursor(data->cursor);
		write(1, "\n", 1);
		return (1);
	}
	free(build);
	return (0);
}
