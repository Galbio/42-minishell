/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:06:31 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/27 07:22:24 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	add_to_history(char *line)
{
	t_readline	*main;
	char		*value;

	main = get_readline_struct();
	value = ft_strdup(line);
	if (!value)
		return ;
	ft_array_unshift(&main->history, value);
	save_history();
}

t_array	get_history(void)
{
	return (get_readline_struct()->history);
}

int	get_history_maxsize(void)
{
	if (HISTORY_SIZE < 0 || HISTORY_SIZE >= 5000)
		return (5000);
	return (HISTORY_SIZE);
}
