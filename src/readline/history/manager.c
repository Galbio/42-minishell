/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:06:31 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/26 20:23:50 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	add_to_history(char *line)
{
	t_readline_core	*core;
	char			*value;

	core = get_readline_core();
	value = ft_strdup(line);
	if (!value)
		return ;
	ft_array_unshift(&core->history, value);
	save_history();
}

t_array	get_history(void)
{
	return (get_readline_core()->history);
}

void	free_history_entry(int key, void *value)
{
	(void)key;
	free(value);
}

int	get_history_maxsize(void)
{
	if (HISTORY_SIZE < 0 || HISTORY_SIZE >= 5000)
		return (5000);
	return (HISTORY_SIZE);
}
