/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:16:08 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/08 19:03:42 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	read_stdin_keys(char *buffer)
{
	int		byte_read;

	byte_read = read(STDIN_FILENO, buffer, 4095);
	if (byte_read == -1)
	{
		buffer[0] = '\0';
		return (0);
	}
	buffer[byte_read] = '\0';
	return (1);
	return (!(buffer[0] == '\0' && !isatty(STDIN_FILENO)));
}
