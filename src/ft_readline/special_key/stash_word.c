/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:02:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/08 17:45:11 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void	stash_and_delete(t_readline_data *data, char *c, int type)
{
	add_to_stash(&get_readline_struct()->stashed, new_char(c), type);
	if (type == 1)
		delete_key(data);
	else
		backspace_key(data);
}

void	stash_before_in_word_key(t_readline_data *data)
{
	int	include_spaces;

	if (!data->first || !data->current)
		return ;
	clean_stash(get_readline_struct(), 1);
	include_spaces = data->current->sequence[0] == ' ';
	while (data->current
		&& (include_spaces || data->current->sequence[0] != ' '))
	{
		stash_and_delete(data, data->current->sequence, 0);
		if (include_spaces)
			include_spaces = data->current && data->current->sequence[0] == ' ';
	}
}

void	stash_after_in_word_key(t_readline_data *data)
{
	int	include_spaces;

	if (!data->first || (data->current && !data->current->next))
		return ;
	clean_stash(get_readline_struct(), 1);
	if (!data->current)
	{
		include_spaces = data->first->sequence[0] == ' ';
		while (data->first
			&& (include_spaces || data->first->sequence[0] != ' '))
		{
			stash_and_delete(data, data->first->sequence, 1);
			if (data->first)
				include_spaces &= data->first->sequence[0] == ' ';
		}
		return ;
	}
	include_spaces = data->current->next->sequence[0] == ' ';
	while (data->current->next
		&& (include_spaces || data->current->next->sequence[0] != ' '))
	{
		stash_and_delete(data, data->current->next->sequence, 1);
		if (data->current->next)
			include_spaces &= data->current->next->sequence[0] == ' ';
	}
}
