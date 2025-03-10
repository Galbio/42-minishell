/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:11:11 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/10 11:22:49 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char	get_open_quote(const char *stashed)
{
	int		i;
	char	cur_quote;
	char	back_slashed;

	i = 0;
	cur_quote = 0;
	back_slashed = 0;
	while (stashed[i])
	{
		if (stashed[i] == '\\' && !back_slashed)
			back_slashed = 1;
		else if ((stashed[i] == '\'' || stashed[i] == '\"') && !back_slashed)
		{
			if (cur_quote == stashed[i])
				cur_quote = 0;
			else if (cur_quote == 0)
				cur_quote = stashed[i];
		}
		else
			back_slashed = 0;
		i++;
	}
	return (cur_quote);
}

void	init_terminal_size(t_vector2 *size)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	size->x = w.ws_col;
	size->y = w.ws_row;
}

t_vector2	get_terminal_size(t_readline *data, int check_resize)
{
	struct winsize	w;
	t_vector2		size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	size.x = w.ws_col;
	size.y = w.ws_row;
	if (check_resize
		&& (size.x != data->old_tsize.x || size.y != data->old_tsize.y))
		on_resize(data, size);
	return (size);
}
