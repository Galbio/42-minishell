/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:11:34 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/06 10:14:17 by gakarbou         ###   ########.fr       */
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
	t_readline		data;
	char			*buffer;
	struct termios	raw;

	enable_raw_mode(&raw);
	write(1, prompt, ft_strlen(prompt));
	init_readline(prompt, &data);
	buffer = NULL;
	while (1)
	{
		buffer = read_stdin_key();
		if (!buffer)
			break ;
		data.update = 1;
		if (process_input(&data, buffer))
			break ;
		handle_key_input(&data, buffer);
		free(buffer);
		buffer = NULL;
		on_write(&data);
	}
	free(buffer);
	disable_raw_mode(&raw);
	return (build_result(data));
}
