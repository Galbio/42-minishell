/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:11:34 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/27 08:06:52 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static t_readline	*rl(t_readline *value)
{
	static t_readline	*data = NULL;

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
	enable_raw_mode();
	write(2, prompt, ft_strlen(prompt));
	rl(data);
	data->prompt = prompt;
	init_terminal_size(&data->old_tsize);
	data->pos.x = -1;
	data->pos.y = -1;
	get_cursor_position(&data->pos);
	while ((data->pos.x < 0)
		|| (data->pos.y < 0)
		|| (data->pos.x > data->old_tsize.x)
		|| (data->pos.y > data->old_tsize.y))
		get_cursor_position(&data->pos);
	data->cursor = data->pos;
	data->first = NULL;
	data->actual = data->first;
	data->exit = 0;
	data->interrupt = 0;
	data->history_index = 0;
	data->current_input = NULL;
}

static char	*leave_readline(t_readline *data, char *res)
{
	disable_raw_mode();
	if (data->interrupt)
		free_readline_core();
	else
		free_readline_data(data);
	show_cursor();
	if (data->interrupt)
		return (NULL);
	if (!res && data->exit)
		return (ft_strdup(""));
	return (clean_backslashes(res));
}

char	*ft_readline(const char *prompt)
{
	t_readline		data;
	char			buffer[4096];
	int				i;
	int				count;

	init_readline(prompt, &data);
	while (1)
	{
		read_stdin_keys(buffer);
		i = 0;
		while (buffer[i])
		{
			count = handle_key_input(&data, buffer + i);
			if (data.exit || data.interrupt)
				return (leave_readline(&data, NULL));
			i += count;
		}
		if (i != 0 && process_input(&data, buffer[i - 1]))
			break ;
		if (data.update)
			on_write(&data);
	}
	return (leave_readline(&data, build_result(data, 0)));
}
