/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:24 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/26 19:31:09 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	update_position(t_readline *data, char *build)
{
	t_vector2	size;
	int			prompt_len;

	size = get_terminal_size(data);
	prompt_len = ft_strlen(data->prompt);
	data->pos.y = data->initial_pos.y
		- ((prompt_len + ft_strlen(build)) / size.x);
	if (data->initial_pos.y != size.y)
		data->pos.y += size.y - data->initial_pos.y;
	if (data->pos.y != data->initial_pos.y)
		data->pos.x = prompt_len + 1;
}

void	on_write(t_readline *data)
{
	char		*build;

	if (!data->update)
		return ;
	get_terminal_size(data);
	build = build_result(*data);
	if (data->cursor.y == get_terminal_size(data).y)
	{
		if ((ft_strlen(data->prompt)
				+ (int)ft_strlen(build)) % get_terminal_size(data).x == 0)
		{
			printf("\n");
			move_y(data, -1);
		}
		update_position(data, build);
	}
	teleport_cursor(data->pos);
	ft_putstr_fd(build, 1);
	ft_putstr_fd("\033[K", 1);
	free(build);
	move_cursor(data, 1);
}

void	on_delete(t_readline *data, int deleted)
{
	char	*build;
	int		spaces;

	build = build_result(*data);
	teleport_cursor(data->pos);
	ft_putstr_fd(build, 1);
	spaces = deleted;
	while (spaces-- > 0)
		ft_putchar_fd(' ', 1);
	free(build);
	move_cursor(data, -deleted);
}
