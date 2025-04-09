/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breakline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:23:31 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/09 15:30:05 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	breakline_key(t_readline_data *data)
{
	char	*build;

	build = list_to_string(*data, last_char(data->first));
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
	on_write(data);
}
