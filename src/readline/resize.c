/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:22:14 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/07 16:29:14 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	check_resize(t_readline *data, t_vector2 size)
{
	char	*builded;
	t_char	*last;

	if ((size.x != data->old_tsize.x || size.y != data->old_tsize.y))
	{
		if (data->pos.x != 0)
		{
			builded = build_result(*data, last_char(data->first));
			last = last_char(data->first);
			data->pos.y = data->cursor.y
				- count_low_newlines(data, last) - count_hard_newlines(*data, last);
			free(builded);
		}
		data->old_tsize = size;
	}
}
