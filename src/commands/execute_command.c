/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:04:40 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/24 19:18:41 by gakarbou         ###   ########.fr       */
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
	int		i;

	if (!access(str, X_OK))
		return (ft_strdup(str));
	i = -1;
	while (paths[++i])
	{
		dest = handle_path_join(paths[i], str);
		if (!access(dest, X_OK))
			return (dest);
		free(dest);
	}
	return (NULL);
}

char	*read_whole_fd(int fd)
{
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
	return (dest);
}

char	*get_command_output(char **argv, t_main_envp *imp)
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
		dup2(pipes[1], 1);
		(close(pipes[0]), close(pipes[1]), execve(argv[0], argv,
				imp->envp_cpy));
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
	{
		printf("%s: command not found\n", argv[0]);
		return (NULL);
	}
	temp = argv[0];
	argv[0] = path;
	free(temp);
	return (get_command_output(argv, imp));
}
