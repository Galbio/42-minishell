/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:46:24 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/09 22:41:37 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	on_sigint(t_readline_data *data)
{
	(void)data;
	if (!get_depth(0))
		write(0, "\n", 1);
	set_exit_status(386);
}

void	on_sigquit(t_readline_data *data)
{
	(void)data;
	set_exit_status(387);
}

static void	handle_signals(int id)
{
	if (id == SIGINT)
		on_sigint(NULL);
	else if (id == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		set_exit_status(131);
	}
}

void	init_signals(void)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
}
