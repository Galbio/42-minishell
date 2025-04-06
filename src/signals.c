/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:46:24 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 11:38:57 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(void)
{
	write(0, "\n", 1);
}

static void	handle_sigquit(void)
{
	write(0, "Quit (core dumped)\n", 19);
}

static void	handle_signals(int id)
{
	if (id == SIGINT)
		handle_sigint();
	else if (id == SIGQUIT)
		handle_sigquit();
}

void	init_signals(void)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
}
