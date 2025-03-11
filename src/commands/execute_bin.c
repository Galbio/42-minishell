/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:09:48 by gakarbou          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/05 16:59:09 by gakarbou         ###   ########.fr       */
=======
/*   Updated: 2025/03/05 17:24:54 by gakarbou         ###   ########.fr       */
>>>>>>> refs/heads/main
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
	if (!paths)
		return (NULL);
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

char	*get_command_output(char **argv, t_main_envp *imp)
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
		dup2(pipes[1], 1);
		close(pipes[0]);
		close(pipes[1]);
		execve(argv[0], argv, imp->envp_cpy);
		exit(0);
	}
	close(pipes[1]);
	wait(NULL);
	dest = ft_get_contents(pipes[0]);
	close(pipes[0]);
	return (dest);
}

char	*execute_bin(char **argv, t_main_envp *imp)
{
	char	*path;
	char	*temp;

	path = get_command_path(argv[0], imp->path);
	if (!path)
	{
<<<<<<< HEAD
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
=======
		if (!imp->path)
			ft_putstr_fd("minishell: ", 2);
		printf("%s: command not found\n", argv[0]);
>>>>>>> refs/heads/main
		return (NULL);
	}
	temp = argv[0];
	argv[0] = path;
	free(temp);
	return (get_command_output(argv, imp));
}
