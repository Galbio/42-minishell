/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:45:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/11 19:48:38 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_readline_keys.h"

int	handle_key_input(t_readline_data *data, char *buffer)
{
	int	res;

	if (data->tab_pressed && buffer[0] != TAB_KEY[0])
	{
		data->tab_pressed = 0;
		ft_array_unset(&data->occurences, ft_array_free_entry);
	}
	res = ft_readline_execute_events(data, buffer);
	if (!res && !ft_isprint(buffer[0]))
		res = 1;
	if (res > 0)
	{
		data->update = 0;
		return (res);
	}
	data->update = 1;
	return (process_default_key(data, buffer));
}
