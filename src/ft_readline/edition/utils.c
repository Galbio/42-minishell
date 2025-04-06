/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:43:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/05 22:07:31 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	fix_last_line(t_readline *data, t_vector2 size)
{
	t_char	*last;

	last = last_char(data->first);
	data->pos.y = size.y - count_low_newlines(data, last)
		- count_hard_newlines(*data, last);
}

void	update_position(t_readline *data, t_vector2 size,
		char *build)
{
	if (data->cursor.y == size.y)
	{
		if (((ft_strlen_utf8(data->prompt) * data->display_prompt)
				+ (int)ft_strlen_utf8(last_newline(build)))
			% size.x == 0)
		{
			write(0, "\n", 1);
			move_y(data, -1);
		}
		fix_last_line(data, size);
	}
}

void	print_build(char *build)
{
	int	i;
	int	in;

	in = get_extra_data_in_fd();
	if (!build || !build[0])
	{
		write(in, "\033[K", 3);
		return ;
	}
	i = 0;
	while (i == 0 || (build[i] && build[i - 1] && build[i - 1] != '\n'))
		i++;
	if (i > 1 && build[i - 1] == '\n')
	{
		write(0, build, i - 1);
		write(in, "\033[K\n", 4);
	}
	else if (i == 1 && build[0] == '\n')
		write(in, "\033[K\n", 4);
	else
		write(0, build, i);
	write(in, "\033[K", 3);
	if (i < (int)ft_strlen(build))
		print_build(build + i);
}
