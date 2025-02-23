/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:04:40 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/23 11:06:24 by gakarbou         ###   ########.fr       */
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
	int		len;
	char	*dest;
	char	*temp;

	dest = NULL;
	temp = NULL;
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		dest = ft_securejoin(dest, temp, 1);
		free(temp);
	}
	close(fd);
	len = ft_strlen(dest);
	if (dest[len - 1] == '\n')
		dest[len - 1] = 0;
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
		return (NULL);
	if (!pid)
	{
		if (ft_strncmp(argv[0], "/bin/curl", 9))
			dup2(pipes[1], 1);
		(close(pipes[0]), close(pipes[1]), execve(argv[0], argv, NULL));
		exit(0);
	}
	(close(pipes[1]), wait(NULL));
	dest = read_whole_fd(pipes[0]);
	close(pipes[0]);
	i = -1;
	while (argv[++i])
		free(argv[i]);
	return (free(argv), dest);
}

char	*execute_command(char *str, t_list *envp, t_main_envp *imp)
{
	char	**argv;
	char	*path;
	char	*temp;

	argv = create_command_argv(str, envp, imp);
	path = get_command_path(argv[0], imp->path);
	if (!path)
		return (NULL);
	temp = argv[0];
	argv[0] = path;
	free(temp);
	if (!path)
		printf("%s: command not found\n", str);
	return (get_command_output(argv));
}
