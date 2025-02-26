/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:04:41 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/26 00:12:58 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_cor_char(char c, int fd)
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

void	write_vars(t_list *envp, int fd)
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

char	*ft_export_vars(t_list *envp)
{
	pid_t	pid;
	int		pipes[2];
	char	*dest;

	if (pipe(pipes) < 0)
		return (NULL);
	pid = fork();
	if (pid < 0)
		return (NULL);
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

char	*add_to_envp(char *command, t_list **envp)
{
	char	*dest;
	int		i;

	(void)envp;
	(void)dest;
	i = -1;
	command += 7;
	if ((command[i] != '_') && !ft_isalpha(command[i]))
		return (ft_putstr_fd("error", 2), free(command - 7), NULL);
	while (command[i])
	{
		if (command[i] == '=')
			break ;
		if ((command[i] != '_') && !ft_isalnum(command[i]))
			return (ft_putstr_fd("error", 2), free(command - 7), NULL);
	}
	dest = ft_substr(command, 0, i);
	//ft_unset(
	return (NULL);
}

char	*ft_export(char *command, t_list **envp)
{
	if (command[6])
		return (add_to_envp(command, envp));
	return (free(command), ft_export_vars(*envp));
}
