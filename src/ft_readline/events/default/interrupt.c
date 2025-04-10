/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interrupt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:22:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/11 15:46:34 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_readline_keys.h"

void	ctrl_c_key(t_readline_data *data)
{
	data->cursor = get_char_pos(data, last_char(data->first));
	teleport_cursor(data->cursor);
	write(0, "^C", 2);
	if (ft_readline_must_exit())
		data->interrupt = 1;
	else
		data->exit = 1;
}

void	ctrl_d_key(t_readline_data *data)
{
	if (data->first == NULL)
		data->interrupt = 1;
	delete_key(data);
}
