/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 00:17:28 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/25 00:57:35 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	redirect_herefile(char *filename, t_cmd_params *cmd)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	dup2(fd, 0);
	if (cmd->imp->input_fd)
		close(cmd->imp->input_fd);
	cmd->imp->input_fd = fd;
	return (0);
}

static char	redirect_herestring(char *value, t_cmd_params *cmd)
{
	int		pipes[2];

	if (pipe(pipes) < 0)
		return (1);
	write(pipes[1], value, ft_strlen(value));
	write(pipes[1], "\n", 1);
	close(pipes[1]);
	dup2(pipes[0], 0);
	if (cmd->imp->input_fd)
		close(cmd->imp->input_fd);
	cmd->imp->input_fd = pipes[0];
	return (0);
}

char	redirect_stdin(char *method, char *value, t_cmd_params *cmd)
{
	int		len;

	len = ft_strlen(method);
	if (len == 1)
	{
		if (redirect_herefile(value, cmd))
			return (1);
	}
	else if (len == 3)
	{
		if (redirect_herestring(value, cmd))
			return (1);
	}
	return (0);
}
