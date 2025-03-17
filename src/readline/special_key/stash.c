/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:01:50 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/17 13:55:51 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	add_to_stash(t_char **stashed, t_char *node, int type)
{
	if (!(*stashed))
		*stashed = node;
	else if (type == 0)
		add_char_front(stashed, node);
	else if (type == 1)
		add_char_back(*stashed, node);
}

void	stash_before_key(t_readline *data)
{
	if (!data->first || !data->actual)
		return ;
	free_chars(data->stashed);
	data->stashed = NULL;
	while (data->actual)
	{
		add_to_stash(&data->stashed, new_char(data->actual->c), 0);
		backspace_key(data);
	}
}

void	stash_after_key(t_readline *data)
{
	if (!data->first || (data->actual && !data->actual->next))
		return ;
	free_chars(data->stashed);
	data->stashed = NULL;
	if (!data->actual)
	{
		while (data->first)
		{
			add_to_stash(&data->stashed, new_char(data->first->c), 1);
			delete_key(data);
		}
		return ;
	}
	while (data->actual->next)
	{
		add_to_stash(&data->stashed, new_char(data->actual->next->c), 1);
		delete_key(data);
	}
}

void	stash_before_in_word_key(t_readline *data)
{
	int	allow_spaces;

	if (!data->first || !data->actual)
		return ;
	free_chars(data->stashed);
	data->stashed = NULL;
	allow_spaces = data->actual->c[0] == ' ';
	while (data->actual && (allow_spaces || data->actual->c[0] != ' '))
	{
		add_to_stash(&data->stashed, new_char(data->actual->c), 0);
		backspace_key(data);
		if (allow_spaces)
			allow_spaces = data->actual->c[0] == ' ';
	}
}

void	stash_after_in_word_key(t_readline *data)
{
	int	allow_spaces;

	if (!data->first || (data->actual && !data->actual->next))
		return ;
	free_chars(data->stashed);
	data->stashed = NULL;
	if (!data->actual)
	{
		allow_spaces = data->first->c[0] == ' ';
		while (data->first && (allow_spaces || data->first->c[0] != ' '))
		{
			add_to_stash(&data->stashed, new_char(data->first->c), 1);
			delete_key(data);
			if (allow_spaces)
				allow_spaces = data->first->c[0] == ' ';
		}
		return ;
	}
	allow_spaces = data->actual->next->c[0] == ' ';
	while (data->actual->next && (allow_spaces || data->actual->next->c[0] != ' '))
	{
		add_to_stash(&data->stashed, new_char(data->actual->next->c), 1);
		delete_key(data);
		if (allow_spaces)
			allow_spaces = data->actual->next->c[0] == ' ';
	}
}

void	paste_stash_key(t_readline *data)
{
	t_char	*cur;

	cur = data->stashed;
	while (cur)
	{
		process_default_key(data, cur->c);
		cur = cur->next;
	}
	on_write(data);
}
