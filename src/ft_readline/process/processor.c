/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:50:35 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 16:01:49 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_readline_keys.h"

int	process_input(t_readline_data *data, char last_c)
{
	char		*build;
	int			res;

	build = list_to_string(*data, last_char(data->first));
	res = (last_c == '\n' || last_c == CTRL_O_KEY[0])
		&& check_quotes(build) && check_backslashes(build);
	free(build);
	return (res);
}

static int	create_value(char *value, char *buffer)
{
	int	len;
	int	i;

	len = ft_bytes_count(buffer[0]);
	i = 0;
	while (i < len)
	{
		value[i] = buffer[i];
		i++;
	}
	while (i < 4)
	{
		value[i] = '\0';
		i++;
	}
	return (len);
}

int	process_default_key(t_readline_data *data, char *buffer)
{
	int		len;
	char	value[4];

	len = create_value(value, buffer);
	if (!data->first)
	{
		data->first = new_char(value);
		data->current = data->first;
	}
	else
	{
		if (!data->current && data->first)
		{
			add_char_front(&data->first, new_char(value));
			data->current = data->first;
			write(1, MOVE_CURSOR_RIGHT, 3);
		}
		else
		{
			add_char_after(&data->current, new_char(value));
			data->current = data->current->next;
		}
	}
	return (len);
}
