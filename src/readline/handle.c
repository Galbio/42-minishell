/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:45:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/14 16:28:19 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int	ft_bytes_count(char c)
{
	if ((c & 0xE0) == 0xC0)
		return (2);
	if ((c & 0xF0) == 0xE0)
		return (3);
	if ((c & 0xF8) == 0xF0)
		return (4);
	return (1);
}

int	process_default_key(t_readline *data, char *buffer)
{
	int		len;
	int		i;
	char	value[4];

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
	data->size += 1;
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
