/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interrupt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:22:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/27 08:26:27 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	ctrl_c_key(t_readline *data)
{
	data->cursor = get_char_pos(data, last_char(data->first));
	teleport_cursor(data->cursor);
	write(0, "^C", 2);
	write(1, "\n", 1);
	if (ft_readline_must_exit())
		data->interrupt = 1;
	else
		data->exit = 1;
}

void	ctrl_d_key(t_readline *data)
{
	if (data->first == NULL)
	{
		write(0, "\nexit", 5);
		data->interrupt = 1;
	}
	delete_key(data);
}
