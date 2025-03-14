/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:11:34 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/14 12:41:41 by lroussel         ###   ########.fr       */
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
	char			buffer[4096];
	struct termios	raw;
	int	i;
	int	count;

	enable_raw_mode(&raw);
	write(1, prompt, ft_strlen(prompt));
	init_readline(prompt, &data);
	while (1)
	{
		read_stdin_keys(buffer);
		data.update = 1;
		i = 0;
		while (buffer[i])
		{
			count = handle_key_input(&data, buffer + i);
			//ft_putnbr_fd(count, 1);
			i += count;
		}
		if (i != 0 && process_input(&data, buffer[i - 1]))
			break ;
		if (data.update)
			on_write(&data);
	}
	disable_raw_mode(&raw);
	return (build_result(data, 0));
}
