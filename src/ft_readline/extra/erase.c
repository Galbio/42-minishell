/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:16:00 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 15:17:50 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_readline_keys.h"

void	erase_after_cursor(int fd, int new_line)
{
	write(fd, ERASE_AFTER_CURSOR, 3);
	if (new_line)
		write(fd, "\n", 1);
}
