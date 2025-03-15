/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 06:13:23 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/14 23:20:15 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct termios	*old(void)
{
	static struct termios	term;
	static int				initialized = 0;

	if (!initialized)
	{
		tcgetattr(STDIN_FILENO, &term);
		initialized = 1;
	}
	return (&term);
}

void	enable_raw_mode(void)
{
	struct termios	raw;

	old();
	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHO | ICANON);
	raw.c_cc[VINTR] = 1;
	raw.c_cc[VQUIT] = 1;
	raw.c_cc[VSUSP] = 1;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void	disable_raw_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, old());
}
