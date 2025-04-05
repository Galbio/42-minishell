/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breakline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:23:31 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/26 18:32:36 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	breakline_key(t_readline *data)
{
	char	*build;

	build = build_result(*data, 0);
	if (check_quotes(build) && check_backslashes(build))
	{
		free(build);
		end_key(data);
		write(0, "\n", 1);
		data->cursor.y++;
		data->cursor.x = 0;
		teleport_cursor(data->cursor);
		return ;
	}
	free(build);
	process_default_key(data, "\n");
	write(0, "\n", 1);
	teleport_cursor(data->cursor);
	on_write(data);
}
