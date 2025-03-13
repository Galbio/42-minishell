/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:46:24 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/13 15:49:44 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(void)
{
	write(1, "\n", 1);
}

static void	handle_signals(int id)
{
	if (id == SIGINT)
		handle_sigint();
}

void	init_signals(void)
{
	signal(SIGINT, handle_signals);
}
