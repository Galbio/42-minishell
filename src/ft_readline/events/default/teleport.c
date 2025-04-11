/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:21:37 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/08 15:15:01 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	home_key(t_readline_data *data)
{
	data->current = NULL;
	data->cursor = get_char_pos(data, data->current);
	teleport_cursor(data->cursor);
}

void	end_key(t_readline_data *data)
{
	data->current = last_char(data->first);
	data->cursor = get_char_pos(data, data->current);
	teleport_cursor(data->cursor);
}

void	previous_word_key(t_readline_data *data)
{
	int	include_spaces;

	if (!data->first || !data->current)
		return ;
	include_spaces = 1;
	while (data->current
		&& (include_spaces || data->current->sequence[0] != ' '))
	{
		include_spaces &= data->current->sequence[0] == ' ';
		data->current = data->current->previous;
	}
	data->cursor = get_char_pos(data, data->current);
	teleport_cursor(data->cursor);
}

void	next_word_key(t_readline_data *data)
{
	int	include_spaces;

	if (!data->first || (data->current && !data->current->next))
		return ;
	if (data->first && !data->current)
		data->current = data->first;
	include_spaces = 1;
	while (data->current->next
		&& (include_spaces || data->current->next->sequence[0] != ' '))
	{
		data->current = data->current->next;
		include_spaces &= data->current->sequence[0] == ' ';
	}
	data->cursor = get_char_pos(data, data->current);
	teleport_cursor(data->cursor);
}
