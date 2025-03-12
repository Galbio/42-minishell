/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:09:48 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/12 15:16:28 by gakarbou         ###   ########.fr       */
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

void	execute_bin(char **argv, t_main_envp *imp)
{
	pid_t	pid;
	char	*path;
	char	*temp;

	path = get_command_path(argv[0], imp->path);
	if (!path)
	{
		if (!imp->path)
			ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return ;
	}
	temp = argv[0];
	argv[0] = path;
	free(temp);
	pid = fork();
	if (pid < 0)
		return ;
	if (!pid)
	{
		dup2(imp->output_fd, 1);
		execve(argv[0], argv, imp->envp_cpy);
	}
	waitpid(pid, NULL, 0);
}
