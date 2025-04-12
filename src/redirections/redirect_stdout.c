/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_stdout.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:43:25 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/12 17:15:56 by gakarbou         ###   ########.fr       */
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

static char	redirect_tofile(t_redirection *redir)
{
	int		fd;

	if (redir->is_fd)
		return (redirect_fd_adress(redir->method, redir->values[0]));
	if (redirection_file_errors(redir->values, redir->og_str))
		return (1);
	unlink(redir->values[0]);
	fd = open(redir->values[0], O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		return (1);
	if (redir->method[0] == '>')
		dup2(fd, 1);
	if (redirect_fd(redir->method, fd))
	{
		close(fd);
		return (1);
	}
	return (0);
}

static char	redirect_appendfile(char *method, char **values)
{
	int		fd;

	if (redirection_file_errors(values, ""))
		return (1);
	fd = open(values[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
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

char	redirect_stdout(t_redirection *redir)
{
	int		i;

	i = 0;
	while (!ft_strchr("<>", redir->method[i]))
		i++;
	if (!redir->method[i + 1])
		return (redirect_tofile(redir));
	if (!ft_strncmp(">>", redir->method + i, 3))
		return (redirect_appendfile(redir->method, redir->values));
	return (0);
}
