/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breakline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:23:31 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/14 15:49:06 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	on_press_breakline_key(t_readline *data)
{
	char	*build;

	build = build_result(*data, 0);
	if (get_open_quote(build) == 0)
	{
		on_press_end_key(data);
		if (data->cursor.y != get_terminal_size(data, 0).y)
		{
			write(0, "\n", 1);
			data->cursor.y++;
		}
		data->cursor.x = 0;
		teleport_cursor(data->cursor);
		return ;
	}
	process_default_key(data, "\n");
	on_write(data);
}
