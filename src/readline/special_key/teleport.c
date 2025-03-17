/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:21:37 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/17 13:26:04 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	home_key(t_readline *data)
{
	data->actual = NULL;
	data->cursor = get_char_pos(data, data->actual);
	teleport_cursor(data->cursor);
}

void	end_key(t_readline *data)
{
	data->actual = last_char(data->first);
	data->cursor = get_char_pos(data, data->actual);
	teleport_cursor(data->cursor);
}

void	previous_word_key(t_readline *data)
{
	int	allow_spaces;

	if (!data->first || !data->actual)
		return ;
	allow_spaces = 1;
	while (data->actual && (allow_spaces || data->actual->c[0] != ' '))
	{
		if (allow_spaces)
			allow_spaces = data->actual->c[0] == ' ';
		data->actual = data->actual->previous;
	}
	data->cursor = get_char_pos(data, data->actual);
	teleport_cursor(data->cursor);
}

void	next_word_key(t_readline *data)
{
	int	allow_spaces;

	if (!data->first || (data->actual && !data->actual->next))
		return ;
	if (data->first && !data->actual)
		data->actual = data->first;
	allow_spaces = 1;
	while (data->actual->next
		&& (allow_spaces || data->actual->next->c[0] != ' '))
	{
		data->actual = data->actual->next;
		if (allow_spaces)
			allow_spaces = data->actual->c[0] == ' ';
	}
	data->cursor = get_char_pos(data, data->actual);
	teleport_cursor(data->cursor);
}
