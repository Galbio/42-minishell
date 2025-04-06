/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breakline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:23:31 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/05 21:57:55 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	breakline_key(t_readline_data *data)
{
	char	*build;

	build = list_to_string(*data, 0);
	if (check_quotes(build) && check_backslashes(build))
	{
		free(build);
		end_key(data);
		write(get_extra_data_in_fd(), "\n", 1);
		data->cursor.y++;
		data->cursor.x = 0;
		teleport_cursor(data->cursor);
		return ;
	}
	free(build);
	process_default_key(data, "\n");
	write(get_extra_data_in_fd(), "\n", 1);
	teleport_cursor(data->cursor);
	on_write(data);
}
