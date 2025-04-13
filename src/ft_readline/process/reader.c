/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:16:08 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/13 18:12:01 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	read_stdin_keys(char *buffer, int is_pipe)
{
	int		byte_read;

	byte_read = read(STDIN_FILENO, buffer, 4095);
	if (byte_read == -1)
	{
		buffer[0] = '\0';
		return (0);
	}
	buffer[byte_read] = '\0';
	return (!is_pipe || buffer[0]);
}
