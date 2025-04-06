/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:45:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/17 17:52:43 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static int	handle_special_keys(t_readline_data *data, char *buffer)
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

int	handle_key_input(t_readline_data *data, char *buffer)
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
