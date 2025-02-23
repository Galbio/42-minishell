/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:27:29 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/23 21:16:48 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*create_line(int byte_read, char **stashed, char **buffer)
{
	char	*temp;
	char	*res;

	if (byte_read <= 0 && !(*stashed) && (*buffer)[0] == '\0')
	{
		free(*buffer);
		return (NULL);
	}
	temp = recover_stashed(*buffer, *stashed);
	free(*buffer);
	if (!temp)
		return (NULL);
	res = seperate(temp, &(*stashed));
	free(temp);
	if (!res[0])
	{
		free(res);
		return (NULL);
	}
	if (!(*stashed) && byte_read == -1)
		free(*stashed);
	return (res);
}

void	*on_error(char **buffer, char **stashed)
{
	free(*buffer);
	*buffer = NULL;
	if (*stashed)
	{
		free(*stashed);
		*stashed = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	int			byte_read;
	char		*buffer;
	static char	*stashed[1024];
	int			pos;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	pos = 0;
	while (1)
	{
		byte_read = read(fd, buffer + pos, BUFFER_SIZE);
		if (byte_read == -1)
			return (on_error(&buffer, &(stashed[fd])));
		buffer[byte_read + pos] = '\0';
		if (byte_read == 0 || ft_strchr(buffer, '\n'))
			break ;
		pos += byte_read;
		buffer = ft_realloc(buffer, pos + 1, pos + BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
	}
	return (create_line(byte_read, &(stashed[fd]), &buffer));
}

char	*recover_stashed(char *buffer, char *stashed)
{
	char	*res;

	if (!stashed)
		return (ft_strdup(buffer));
	res = malloc(ft_strlen(buffer) + ft_strlen(stashed) + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, stashed, ft_strlen(stashed) + 1);
	ft_strlcpy(res + ft_strlen(stashed), buffer, ft_strlen(buffer) + 1);
	return (res);
}

char	*seperate(char *buffer, char **stashed)
{
	int		i;
	char	*res;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	res = ft_strdup(buffer);
	if (!res)
		return (NULL);
	res[i] = '\0';
	if (*stashed)
	{
		free(*stashed);
		*stashed = NULL;
	}
	if (buffer[i])
		*stashed = ft_strdup(buffer + i);
	return (res);
}
