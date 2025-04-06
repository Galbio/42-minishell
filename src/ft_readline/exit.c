/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:00:34 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 13:59:28 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static int	ext(int v)
{
	static int	must_exit = 1;

	if (v == 0 || v == 1)
		must_exit = v;
	return (must_exit);
}

void	ft_readline_set_exit(int v)
{
	ext(v);
}

int	ft_readline_must_exit(void)
{
	return (ext(2));
}

void	free_readline_core(void)
{
	t_readline	*core;

	core = get_readline_core();
	ft_array_unset(&core->special_keys, ft_array_free_entry);
	free_chars(core->stashed);
	ft_array_unset(&core->history, ft_array_free_entry);
	free(core);
}

void	free_readline_data(t_readline_data *data)
{
	if (!data)
		return ;
	free_chars(data->first);
	data->actual = NULL;
	data->first = NULL;
	free_chars(data->current_input);
	data->current_input = NULL;
}
