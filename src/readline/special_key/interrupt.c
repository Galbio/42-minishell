/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interrupt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:22:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/26 20:16:47 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	ctrl_c_key(t_readline *data)
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

void	ctrl_d_key(t_readline *data)
{
	t_array	history;

	if (data->first == NULL)
	{
		disable_raw_mode();
		history = get_history();
		ft_array_unset(&history, free_history_entry);
		free_ft_readline(data);
		write(0, "\nexit\n", 6);
		exit(0);
	}
	delete_key(data);
}
