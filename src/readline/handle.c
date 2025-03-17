/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:45:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/17 11:31:13 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

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

int	process_default_key(t_readline *data, char *buffer)
{
	int		len;
	char	value[4];

	len = create_value(value, buffer);
	if (!data->first)
	{
		data->first = new_char(value);
		data->actual = data->first;
	}
	else
	{
		if (!data->actual && data->first)
		{
			add_char_front(&data->first, new_char(value));
			data->actual = data->first;
			write(1, "\033[C", 3);
		}
		else
		{
			add_char_after(&data->actual, new_char(value));
			data->actual = data->actual->next;
		}
	}
	return (len);
}

int	handle_special_keys(t_readline *data, char *buffer)
{
	t_special_key	*key;

	key = get_by_sequence(buffer);
	if (key)
	{
		get_terminal_size(data, 1);
		(key->callback)(data);
		return (ft_strlen(key->sequence));
	}
	if (!ft_isprint(buffer[0]))
		return (1);
	return (0);
}

int	handle_key_input(t_readline *data, char *buffer)
{
	int	res;

	res = handle_special_keys(data, buffer);
	if (res > 0)
	{
		data->update = 0;
		return (res);
	}
	data->update = 1;
	return (process_default_key(data, buffer));
}
