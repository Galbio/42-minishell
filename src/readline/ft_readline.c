/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:11:34 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/26 15:55:00 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	init_readline(t_readline *data)
{
	get_cursor_position(&data->pos.x, &data->pos.y);
	data->first = NULL;
	data->actual = data->first;
	data->size = 0;
}

char	*ft_readline(const char *prompt)
{
	t_readline	data;
	char		*buffer;

	init_readline(&data);
	write(1, prompt, ft_strlen(prompt));
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
		update_terminal(&data, prompt);
		free(buffer);
		buffer = NULL;
	}
	free(buffer);
	return (build_result(data));
}
