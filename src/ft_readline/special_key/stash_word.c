/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:02:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 15:46:05 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void	stash_and_delete(t_readline *main, t_readline_data *data,
		char *c, int type)
{
	add_to_stash(&main->stashed, new_char(c), type);
	if (type == 1)
		delete_key(data);
	else
		backspace_key(data);
}

void	stash_before_in_word_key(t_readline_data *data)
{
	t_readline	*main;
	int			as;

	if (!data->first || !data->current)
		return ;
	main = get_readline_struct();
	clean_stash(main, 1);
	as = data->current->sequence[0] == ' ';
	while (data->current && (as || data->current->sequence[0] != ' '))
	{
		stash_and_delete(main, data, data->current->sequence, 0);
		if (as)
			as = data->current->sequence[0] == ' ';
	}
}

void	stash_after_in_word_key(t_readline_data *data)
{
	t_readline	*main;
	int			as;

	if (!data->first || (data->current && !data->current->next))
		return ;
	main = get_readline_struct();
	clean_stash(main, 1);
	if (!data->current)
	{
		as = data->first->sequence[0] == ' ';
		while (data->first && (as || data->first->sequence[0] != ' '))
		{
			stash_and_delete(main, data, data->first->sequence, 1);
			if (data->first)
				as &= data->first->sequence[0] == ' ';
		}
		return ;
	}
	as = data->current->next->sequence[0] == ' ';
	while (data->current->next && (as || data->current->next->sequence[0] != ' '))
	{
		stash_and_delete(main, data, data->current->next->sequence, 1);
		if (data->current->next)
			as &= data->current->next->sequence[0] == ' ';
	}
}
