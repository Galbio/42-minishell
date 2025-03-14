/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:21:37 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/14 14:21:47 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	on_press_home_key(t_readline *data)
{
	data->actual = NULL;
	data->cursor = get_char_pos(data, data->actual);
	teleport_cursor(data->cursor);
}

void	on_press_end_key(t_readline *data)
{
	data->actual = last_char(data->first);
	data->cursor = get_char_pos(data, data->actual);
	teleport_cursor(data->cursor);
}
