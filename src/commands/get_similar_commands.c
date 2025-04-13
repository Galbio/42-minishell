/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_similar_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:11:05 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/13 02:21:17 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_similar_cmds(int pipes[2], char *cmd_name)
{
	char	**av;

	close(pipes[0]);
	dup2(pipes[1], 2);
	av = malloc(sizeof(char *) * 3);
	if (av)
	{
		av[0] = ft_strdup("/usr/lib/command-not-found");
		av[1] = ft_strdup(cmd_name);
		av[2] = NULL;
	}
	execve("/usr/lib/command-not-found", av, NULL);
	close(pipes[1]);
	exit(1);
}

char	*get_similar_commands(char *cmd_name)
{
	char	*content;
	int		pipes[2];
	pid_t	pid;

	if (pipe(pipes))
		return (NULL);
	pid = fork();
	if (!pid)
		execute_similar_cmds(pipes, cmd_name);
	close(pipes[1]);
	waitpid(pid, NULL, 0);
	content = ft_get_contents(pipes[0]);
	close(pipes[0]);
	return (content);
}
