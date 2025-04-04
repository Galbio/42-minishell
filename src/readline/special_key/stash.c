/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:01:50 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/17 17:02:17 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	stash_before_key(t_readline *data)
{
	t_readline_core	*core;

	if (!data->first || !data->actual)
		return ;
	core = get_readline_core();
	clean_stash(core, 0);
	while (data->actual)
	{
		add_to_stash(&core->stashed, new_char(data->actual->c), 0);
		backspace_key(data);
	}
}

void	stash_after_key(t_readline *data)
{
	t_readline_core	*core;

	if (!data->first || (data->actual && !data->actual->next))
		return ;
	core = get_readline_core();
	clean_stash(core, 0);
	if (!data->actual)
	{
		while (data->first)
		{
			add_to_stash(&core->stashed, new_char(data->first->c), 1);
			delete_key(data);
		}
		return ;
	}
	while (data->actual->next)
	{
		add_to_stash(&core->stashed, new_char(data->actual->next->c), 1);
		delete_key(data);
	}
}

void	paste_stash_key(t_readline *data)
{
	t_char			*cur;
	t_readline_core	*core;

	core = get_readline_core();
	core->cat_stash = 0;
	cur = core->stashed;
	while (cur)
	{
		process_default_key(data, cur->c);
		cur = cur->next;
	}
	on_write(data);
}
