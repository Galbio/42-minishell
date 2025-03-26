/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:00:34 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/26 21:14:44 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

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
	t_readline_core	*core;
	int				i;

	core = get_readline_core();
	i = 0;
	while (core->special_keys[i])
	{
		free(core->special_keys[i]);
		i++;
	}
	free(core->special_keys);
	free_chars(core->stashed);
	free(core);
}

void	free_readline_data(t_readline *data)
{
	if (!data)
		return ;
	free_chars(data->first);
	data->actual = NULL;
	data->first = NULL;
}
