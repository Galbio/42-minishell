/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:09:48 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/09 22:24:35 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_path_join(char *path, char *str)
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

static char	*get_command_path(char *str, char **paths)
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

static void	cmd_not_found(t_cmd_params *cmd)
{
	if (!cmd->imp->path)
		ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_cmd(cmd, 1);
	free_envp(cmd->envp, cmd->imp);
	free(cmd);
	exit(127);
}

void	execute_bin(t_cmd_params *cmd)
{
	char	*path;
	char	**argv;
	char	**envp_cpy;

	get_depth(-1);
	path = get_command_path(cmd->argv[0], cmd->imp->path);
	if (!path)
		cmd_not_found(cmd);
	argv = cmd->argv;
	envp_cpy = create_envp_cpy(cmd->envp, cmd->imp);
	free_cmd(cmd, 'b');
	free_envp(cmd->envp, cmd->imp);
	free(cmd);
	execve(path, argv, envp_cpy);
	exit(1);
}
