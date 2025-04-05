/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:02:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/17 17:10:54 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	stash_and_delete(t_readline_core *core, t_readline *data,
		char *c, int type)
{
	add_to_stash(&core->stashed, new_char(c), type);
	if (type == 1)
		delete_key(data);
	else
		backspace_key(data);
}

void	stash_before_in_word_key(t_readline *data)
{
	t_readline_core	*core;
	int				as;

	if (!data->first || !data->actual)
		return ;
	core = get_readline_core();
	clean_stash(core, 1);
	as = data->actual->c[0] == ' ';
	while (data->actual && (as || data->actual->c[0] != ' '))
	{
		stash_and_delete(core, data, data->actual->c, 0);
		if (as)
			as = data->actual->c[0] == ' ';
	}
}

void	stash_after_in_word_key(t_readline *data)
{
	t_readline_core	*core;
	int				as;

	if (!data->first || (data->actual && !data->actual->next))
		return ;
	core = get_readline_core();
	clean_stash(core, 1);
	if (!data->actual)
	{
		as = data->first->c[0] == ' ';
		while (data->first && (as || data->first->c[0] != ' '))
		{
			stash_and_delete(core, data, data->first->c, 1);
			if (data->first)
				as &= data->first->c[0] == ' ';
		}
		return ;
	}
	as = data->actual->next->c[0] == ' ';
	while (data->actual->next && (as || data->actual->next->c[0] != ' '))
	{
		stash_and_delete(core, data, data->actual->next->c, 1);
		if (data->actual->next)
			as &= data->actual->next->c[0] == ' ';
	}
}
