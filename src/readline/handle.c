/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:45:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/26 19:37:12 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	handle_key_input(t_readline *data, char *buffer)
{
	if (process_special_keys(data, buffer))
	{
		data->update = 0;
		return ;
	}
	if (!data->first)
	{
		data->first = new_char(buffer[0]);
		data->actual = data->first;
	}
	else
	{
		if (!data->actual && data->first)
		{
			add_char_front(&data->first, new_char(buffer[0]));
			write(1, "\033[C", 3);
		}
		else
		{
			add_char_after(&data->actual, new_char(buffer[0]));
			data->actual = data->actual->next;
		}
	}
	data->size++;
}
