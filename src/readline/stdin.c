/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:16:08 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/26 15:56:14 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	read_extra(char **buffer, int times)
{
	int		i;
	int		byte_read;
	char	*new;

	new = ft_realloc(*buffer, sizeof (char) * 2, sizeof(char) * (2 + times));
	if (!new)
	{
		free(*buffer);
		*buffer = NULL;
		return ;
	}
	*buffer = new;
	i = 1;
	while (times-- > 0)
	{
		byte_read = read(STDIN_FILENO, *buffer + i, 1);
		if (byte_read == -1)
		{
			free(*buffer);
			*buffer = NULL;
			return ;
		}
		i++;
	}
}

char	*read_stdin_key(void)
{
	char	*buffer;
	int		byte_read;

	buffer = malloc(sizeof(char) * (2));
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, 2);
	byte_read = read(STDIN_FILENO, buffer, 1);
	if (byte_read == -1)
	{
		free(buffer);
		return (NULL);
	}
	if (buffer[0] == '\033')
		read_extra(&buffer, 2);
	return (buffer);
}
