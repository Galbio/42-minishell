/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breakline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:23:31 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/15 20:00:22 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	breakline_key(t_readline *data)
{
	char	*build;

	build = build_result(*data, 0);
	if (get_open_quote(build) == 0)
	{
		end_key(data);
		write(0, "\n", 1);
		data->cursor.y++;
		data->cursor.x = 0;
		teleport_cursor(data->cursor);
		return ;
	}
	process_default_key(data, "\n");
	write(0, "\n", 1);
	teleport_cursor(data->cursor);
	on_write(data);
}
