/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_stdout.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:43:25 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 10:44:28 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	redirect_fd(char *str, int fd)
{
	int		nb;

	if (*str == '&')
	{
		dup2(fd, 1);
		dup2(1, 2);
		return (0);
	}
	if (!ft_isdigit(*str))
		return (0);
	nb = ft_atoi(str);
	if (nb >= 1024)
	{
		write(2, "minishell: ", 12);
		ft_putnbr_fd(nb, 2);
		write(2, ": Bad file descriptor\n", 22);
		return (1);
	}
	dup2(fd, nb);
	return (0);
}

static char	redirect_fd_adress(char *src, char *dest)
{
	int		src_nb;
	int		dest_nb;

	if (!ft_isdigit(src[0]))
		src_nb = 1;
	else
		src_nb = ft_atoi(src);
	if (!ft_isdigit(dest[0]))
		dest_nb = 1;
	else
		dest_nb = ft_atoi(dest);
	if ((src_nb >= 1024) || (dest_nb >= 1024))
		return (1);
	dup2(dest_nb, src_nb);
	return (0);
}

static char	redirect_tofile(char *method, char **name)
{
	int		fd;

	if (name[0])
		return (redirect_fd_adress(method, name[1]));
	fd = open(name[1], O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		return (1);
	if (method[0] == '>')
		dup2(fd, 1);
	if (redirect_fd(method, fd))
	{
		close(fd);
		return (1);
	}
	return (0);
}

static char	redirect_appendfile(char *method, char **name)
{
	int		fd;

	fd = open(name[1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
		return (1);
	if (method[0] == '>')
		dup2(fd, 1);
	if (redirect_fd(method, fd))
	{
		close(fd);
		return (1);
	}
	return (0);
}

char	redirect_stdout(char *method, char **value)
{
	int		i;

	if (!value[1])
	{
		write(2, "minishell: syntax error ", 24);
		write(2, "near unexpected token `newline'\n", 32);
		return (1);
	}
	i = 0;
	while (!ft_strchr("<>", method[i]))
		i++;
	if (!method[i + 1])
		return (redirect_tofile(method, value));
	if (!ft_strncmp(">>", method + i, 3))
		return (redirect_appendfile(method, value));
	return (0);
}
