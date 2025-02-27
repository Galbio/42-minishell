/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:40:47 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/27 18:43:35 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_cor_char(char c, int fd)
{
	if (c == '"')
		write(fd, "\\\"", 2);
	else if (c == '\\')
		write(fd, "\\\\", 2);
	else if (c == '\n')
		write(fd, "\\n", 2);
	else if (c == '\t')
		write(fd, "\\t", 2);
	else if (c == '\v')
		write(fd, "\\v", 2);
	else if (c == '\r')
		write(fd, "\\r", 2);
	else if (c == '\f')
		write(fd, "\\f", 2);
	else
		write(fd, &c, 1);
}

static void	write_vars(t_list *envp, int fd)
{
	char	*env;
	int		i;

	while (envp)
	{
		env = (char *)envp->content;
		ft_putstr_fd("declare -x ", fd);
		i = -1;
		while (env[++i] && env[i] != '=')
			write(fd, env + i, 1);
		if (!env)
			return ;
		write(fd, "=\"", 2);
		while (env[++i])
			write_cor_char(env[i], fd);
		write(fd, "\"\n", 2);
		envp = envp->next;
	}
}

char	*export_vars(t_list *envp)
{
	pid_t	pid;
	int		pipes[2];
	char	*dest;

	if (pipe(pipes) < 0)
		return (NULL);
	pid = fork();
	if (pid < 0)
	{
		close(pipes[0]);
		close(pipes[1]);
		return (NULL);
	}
	if (!pid)
	{
		(close(pipes[0]), write_vars(envp, pipes[1]));
		(close(pipes[1]), exit(0));
	}
	(close(pipes[1]), wait(NULL));
	dest = read_whole_fd(pipes[0]);
	close(pipes[0]);
	return (dest);
}
