/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:01:50 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 15:47:23 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	stash_before_key(t_readline_data *data)
{
	t_readline	*main;

	if (!data->first || !data->current)
		return ;
	main = get_readline_struct();
	clean_stash(main, 0);
	while (data->current)
	{
		add_to_stash(&main->stashed, new_char(data->current->sequence), 0);
		backspace_key(data);
	}
}

void	stash_after_key(t_readline_data *data)
{
	t_readline	*main;

	if (!data->first || (data->current && !data->current->next))
		return ;
	main = get_readline_struct();
	clean_stash(main, 0);
	if (!data->current)
	{
		while (data->first)
		{
			add_to_stash(&main->stashed, new_char(data->first->sequence), 1);
			delete_key(data);
		}
		return ;
	}
	while (data->current->next)
	{
		add_to_stash(&main->stashed, new_char(data->current->next->sequence), 1);
		delete_key(data);
	}
}

void	paste_stash_key(t_readline_data *data)
{
	t_readline_char		*cur;
	t_readline			*main;

	main = get_readline_struct();
	main->cat_stash = 0;
	cur = main->stashed;
	while (cur)
	{
		process_default_key(data, cur->sequence);
		cur = cur->next;
	}
	on_write(data);
}
