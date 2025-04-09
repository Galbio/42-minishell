/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:46:24 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/09 18:39:47 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sig_exitcode(int v)
{
	static int	code = -1;

	if (v >= -1)
		code = v;
	return (code);
}

void	reset_sig_exitcode(void)
{
	sig_exitcode(-1);
}

int	get_sig_exitcode(void)
{
	return (sig_exitcode(-2));
}

static void	handle_signals(int id)
{
	if (id == SIGINT)
	{
		write(0, "\n", 1);
		sig_exitcode(130);
	}
	else if (id == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		sig_exitcode(131);
	}
}

void	init_signals(void)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
}
