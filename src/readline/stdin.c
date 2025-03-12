/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:16:08 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/12 16:22:13 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/*static void	read_extra(char *buffer)
{
	int	byte_read;

	byte_read = read(STDIN_FILENO, buffer, 48);
	if (byte_read == -1)
		free(buffer);
}*/

void	read_stdin_keys(char *buffer)
{
	int		byte_read;
	byte_read = read(STDIN_FILENO, buffer, 4095);
	buffer[byte_read] = '\0';
	if (byte_read == -1)
		return ;
}
