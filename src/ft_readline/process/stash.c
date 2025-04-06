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

#include "ft_readline.h"

void	add_to_stash(t_char **stashed, t_char *node, int type)
{
	if (!(*stashed))
		*stashed = node;
	else if (type == 0)
		add_char_front(stashed, node);
	else if (type == 1)
		add_char_back(*stashed, node);
}

void	clean_stash(t_readline *main, int check_cat)
{
	if (!check_cat || !main->cat_stash)
	{
		free_chars(main->stashed);
		main->stashed = NULL;
	}
	if (check_cat)
		main->cat_stash = 1;
}
