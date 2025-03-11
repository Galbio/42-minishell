/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:11:34 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/11 11:33:07 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static t_readline	*rl(t_readline *value)
{
	static t_readline	*data;

	if (data == NULL && value)
		data = value;
	return (data);
}

t_readline	*get_readline_data(void)
{
	return (rl(NULL));
}

static void	init_readline(const char *prompt, t_readline *data)
{
	rl(data);
	data->prompt = prompt;
	get_cursor_position(&data->initial_pos);
	data->pos = data->initial_pos;
	data->cursor = data->pos;
	data->first = NULL;
	data->actual = data->first;
	data->size = 0;
	init_terminal_size(&data->old_tsize);
	data->end_line = data->initial_pos.y == data->old_tsize.y;
	data->buffer_ptr = NULL;
	data->exit = 0;
}

char	*ft_readline(const char *prompt)
{
	t_readline	data;
	char		*buffer;
	char		*build;

	write(1, prompt, ft_strlen(prompt));
	init_readline(prompt, &data);
	buffer = NULL;
	while (1)
	{
		buffer = read_stdin_key(&data);
		if (!buffer)
			break ;
		data.update = 1;
		if (process_input(&data, buffer))
			break ;
		handle_key_input(&data, buffer);
		if (data.exit)
		{
			free_ft_readline(&data);
			return (NULL);
		}
		free(buffer);
		buffer = NULL;
		on_write(&data);
	}
	build = build_result(data);
	free_ft_readline(&data);
	return (build);
}
