/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 06:13:23 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/23 19:46:36 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	enable_raw_mode(struct termios *raw)
{
	tcgetattr(STDIN_FILENO, raw);
	raw->c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, raw);
}

void	disable_raw_mode(struct termios *raw)
{
	tcgetattr(STDIN_FILENO, raw);
	raw->c_lflag |= (ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, raw);
}
