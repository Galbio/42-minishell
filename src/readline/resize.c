/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:22:14 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/26 18:42:37 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	check_resize(t_readline *data, t_vector2 size)
{
	int					len;
	char				*builded;

	if ((size.x != data->old_tsize.x || size.y != data->old_tsize.y))
	{
		get_cursor_position(&data->cursor);
		if (data->pos.x != 0)
		{
			builded = build_result(*data);
			len = ft_strlen(builded);
			data->initial_pos.y = data->cursor.y
				- ((ft_strlen(data->prompt) + len) / size.x);
			free(builded);
		}
		data->old_tsize = size;
		data->pos.y = data->initial_pos.y;
	}
}
