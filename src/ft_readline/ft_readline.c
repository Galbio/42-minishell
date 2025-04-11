/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:11:34 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/11 15:05:46 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static char	*leave_readline(t_readline_data *data, char *res)
{
	disable_raw_mode();
	if (ft_readline_is_format_checked() == 0)
	{
		free_readline_data(data);
		return (res);
	}
	if (data->interrupt)
	{
		free_readline();
	}
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
	t_readline_data		data;
	char				buffer[4096];
	int					i;
	int					count;

	init_readline_data(prompt, &data);
	while (1)
	{
		data.interrupt = !read_stdin_keys(buffer);
		if (data.interrupt)
			return (leave_readline(&data, NULL));
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
	return (leave_readline(&data, list_to_string(data, 0)));
}
