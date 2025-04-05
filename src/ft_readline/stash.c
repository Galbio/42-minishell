/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:23:56 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/17 16:50:26 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	add_to_stash(t_char **stashed, t_char *node, int type)
{
	if (!(*stashed))
		*stashed = node;
	else if (type == 0)
		add_char_front(stashed, node);
	else if (type == 1)
		add_char_back(*stashed, node);
}

void	clean_stash(t_readline_core *core, int check_cat)
{
	if (!check_cat || !core->cat_stash)
	{
		free_chars(core->stashed);
		core->stashed = NULL;
	}
	if (check_cat)
		core->cat_stash = 1;
}
