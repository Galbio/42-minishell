/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:46:41 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/25 15:47:16 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	hide_cursor(void)
{
	write(0, HIDE_CURSOR, 6);
}

void	show_cursor(void)
{
	write(0, SHOW_CURSOR, 6);
}
