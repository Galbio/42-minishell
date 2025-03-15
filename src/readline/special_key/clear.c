/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:19:38 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/15 20:29:06 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	clear_key(t_readline *data)
{
	write(0, "\033[2J", 4);
	data->pos.x = 0;
	data->pos.y = 0;
	teleport_cursor(data->pos);
	write(2, data->prompt, ft_strlen(data->prompt));
	get_cursor_position(&data->pos);
	get_cursor_position(&data->cursor);
	teleport_cursor(data->cursor);
	on_write(data);
}
