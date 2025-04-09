/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:44:41 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/09 19:20:38 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

t_readline	*get_readline_struct(void)
{
	static t_readline	*main = NULL;

	if (!main)
	{
		main = malloc(sizeof(t_readline));
		main->events = NULL;
		ft_readline_register_default_events();
		main->stashed = NULL;
		main->cat_stash = 0;
		init_history();
	}
	return (main);
}
