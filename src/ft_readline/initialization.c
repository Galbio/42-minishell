/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:04:04 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/09 17:15:36 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static t_readline_data	*struct_storage(t_readline_data *value)
{
	static t_readline_data	*data = NULL;

	if (data == NULL && value)
		data = value;
	return (data);
}

t_readline_data	*get_readline_data(void)
{
	return (struct_storage(NULL));
}

static void	init_environnement(const char *prompt, t_readline_data *data)
{
	int	len;

	data->pos.x = 0;
	data->pos.y = 0;
	get_cursor_position(&data->pos);
	data->is_pipe = !isatty(STDIN_FILENO);
	init_terminal_size(&data->old_tsize);
	if (!data->is_pipe)
		write(2, prompt, ft_strlen(prompt));
	data->display_prompt = isatty(STDERR_FILENO);
	data->offset = data->pos.x - 1;
	if (data->display_prompt)
	{
		len = ft_strlen(prompt);
		data->pos.x += len;
		data->pos.y += data->pos.x / data->old_tsize.x
			+ ft_strcount_char(prompt, '\n');
		data->pos.x -= len - ft_strlen(ft_getlast_newline((char *)prompt));
		data->pos.x = data->pos.x % data->old_tsize.x;
	}
}

void	init_readline_data(const char *prompt, t_readline_data *data)
{
	enable_raw_mode();
	struct_storage(data);
	init_environnement(prompt, data);
	data->cursor = data->pos;
	data->prompt = prompt;
	data->first = NULL;
	data->current = data->first;
	data->exit = 0;
	data->interrupt = 0;
	data->history_index = 0;
	data->current_input = NULL;
}
