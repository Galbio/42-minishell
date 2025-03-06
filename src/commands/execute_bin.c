/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:09:48 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/06 06:09:05 by gakarbou         ###   ########.fr       */
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

char	*execute_bin(char **argv, t_main_envp *imp)
{
	char	*path;
	char	*temp;

	path = get_command_path(argv[0], imp->path);
	if (!path)
	{
		printf("%s: command not found\n", argv[0]);
		return (NULL);
	}
	temp = argv[0];
	argv[0] = path;
	free(temp);
	execve(argv[0], argv, imp->envp_cpy);
	return (NULL);
}
