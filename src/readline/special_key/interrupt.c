/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interrupt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:22:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/15 19:44:54 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	on_press_ctrl_c_key(t_readline *data)
{
	data->cursor = get_char_pos(data, last_char(data->first));
	teleport_cursor(data->cursor);
	write(0, "^C\n", 3);
	data->exit = 1;
	if (ft_readline_must_exit())
	{
		free_ft_readline(data);
		disable_raw_mode();
		exit(0);
	}
}

void	on_press_ctrl_d_key(t_readline *data)
{
	if (data->first == NULL)
	{
		disable_raw_mode();
		free_ft_readline(data);
		write(0, "\nexit\n", 6);
		exit(0);
	}
	on_press_delete_key(data);
}
