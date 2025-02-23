/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:04:40 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/23 08:04:33 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_path_join(char *path, char *str)
{
	char	*temp;
	char	*dest;
	int		size;

	size = ft_strlen(path);
	if (path[size - 1] == '/')
		return (ft_strjoin(path, str));
	temp = ft_securejoin("/", str, 0);
	dest = ft_securejoin(path, temp, 0);
	free(temp);
	return (dest);
}

char	*get_command_path(char *str, char **paths)
{
	char	*dest;
	int		fd;
	int		i;

	fd = open(str, O_RDONLY);
	if (fd > 0)
	{
		close(fd);
		return (ft_strdup(str));
	}
	i = -1;
	while (paths[++i])
	{
		dest = handle_path_join(paths[i], str);
		fd = open(dest, O_RDONLY);
		if (fd > 0)
		{
			close(fd);
			return (dest);
		}
		free(dest);
	}
	return (NULL);
}

char	*read_whole_fd(int fd)
{
	char	*dest;
	char	*temp;

	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		dest = ft_securejoin(dest, temp, 1);
	}
	close(fd);
	return (dest);
}

char	*get_command_output(char **argv)
{
	pid_t	pid;
	int		i;
	int		pipes[2];
	char	*dest;

	if (pipe(pipes) < 0)
		return (NULL);
	pid = fork();
	if (pid < 0)
	{
		if (ft_strncmp(argv[0], "/bin/curl", 9))
			dup2(pipes[1], 1);
		(close(pipes[0]), close(pipes[1]));
		return (NULL);
	}
	if (pid)
		(close(pipes[0]), close(pipes[1]), execve(argv[0], argv, NULL));
	(close(pipes[1]), wait(NULL));
	dest = read_whole_fd(pipes[0]);
	close(pipes[0]);
	i = -1;
	while (argv[++i])
		free(argv[i]);
	return (free(argv), dest);
}

char	*execute_command(char *str, char **paths)
{
	char	**argv;
	char	*path;
	char	*temp;

	argv = create_command_argv(str);
	path = get_command_path(argv[0], paths);
	if (!path)
		return (NULL);
	temp = argv[0];
	argv[0] = path;
	free(temp);
	if (!path)
		printf("%s: command not found\n", str);
	else
		printf("Command found at %s\n", path);
	return (get_command_output(argv));
}
