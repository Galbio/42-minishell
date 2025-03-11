/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:11:34 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/11 12:18:51 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	init_readline(const char *prompt, t_readline *data)
{
	data->prompt = prompt;
	init_terminal_size(&data->old_tsize);
	get_cursor_position(&data->pos);
	while ((data->pos.x < 0) || (data->pos.y < 0)
		|| (data->pos.x) > (data->old_tsize.x)
		|| (data->pos.y) > (data->old_tsize.y))
		get_cursor_position(&data->pos);
	data->cursor = data->pos;
	data->first = NULL;
	data->actual = data->first;
	data->size = 0;
}

char	*ft_readline(const char *prompt)
{
	t_readline		data;
	char			*buffer;
	struct termios	raw;

	enable_raw_mode(&raw);
	write(1, prompt, ft_strlen(prompt));
	buffer = NULL;
	init_readline(prompt, &data);
	while (1)
	{
		buffer = read_stdin_key();
		if (!buffer)
			break ;
		data.update = 1;
		if (process_input(&data, buffer))
			break ;
		handle_key_input(&data, buffer);
		if (data.update)
			on_write(&data, buffer);
		free(buffer);
		buffer = NULL;
	}
	free(buffer);
	disable_raw_mode(&raw);
	return (build_result(data, 0));
}
