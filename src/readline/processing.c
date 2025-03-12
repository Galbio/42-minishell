/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:30 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/12 16:44:27 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static int	calculate_len(t_readline data, t_char *to)
{
	int		len;
	t_char	*c;

	if (!to)
		return (data.size);
	len = 1;
	c = to;
	while (c->previous)
	{
		len++;
		c = c->previous;
	}
	return (len);
}

char	*build_result(t_readline data, t_char *to)
{
	char	*result;
	t_char	*c;
	int		i;
	int		len;

	if (!data.first || data.first->c == '\n')
		return (ft_strdup(""));
	len = calculate_len(data, to);
	if (!to && data.first && !data.actual)
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
		free(build);
		return (1);
	}
	free(build);
	return (0);
}

int	process_special_keys(t_readline *data, char *buffer)
{
	if ((buffer[0] == 127) && data->size > 0)
		return (delete_char(data));
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 68)
		return (move_cursor_left(data));
	if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 67)
		return (move_cursor_right(data));
	if (buffer[0] == 3)
		return (ctrl_c(data));
	if (buffer[0] == 4)
		ctrl_d(data);
	if (buffer[0] == 28)
		return (1);
	return (!ft_isprint(buffer[0]) && buffer[1]);
}
