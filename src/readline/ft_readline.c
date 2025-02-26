/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:11:34 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/26 18:39:51 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	init_readline(const char *prompt, t_readline *data)
{
	data->prompt = prompt;
	get_cursor_position(&data->initial_pos);
	data->pos = data->initial_pos;
	data->cursor = data->pos;
	data->first = NULL;
	data->actual = data->first;
	data->size = 0;
	init_terminal_size(&data->old_tsize);
	data->end_line = data->initial_pos.y == data->old_tsize.y;
}

char	*ft_readline(const char *prompt)
{
	t_readline	data;
	int			byte_read;
	char		buffer[100];

	write(1, prompt, ft_strlen(prompt));
	init_readline(prompt, &data);
	while (1)
	{
		ft_bzero(buffer, 100);
		byte_read = read(STDIN_FILENO, buffer, 99);
		if (byte_read <= 0)
			break ;
		data.update = 1;
		data.c = *((int *)buffer);
		if (process_input(&data))
			break ;
		handle_key_input(&data, buffer);
		on_write(&data);
	}
	return (build_result(data));
}
