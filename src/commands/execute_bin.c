/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:09:48 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/06 23:02:49 by lroussel         ###   ########.fr       */
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
	t_array	args;

	if (!cmd->imp->path)
		write(2, "minishell: ", 11);
	args = simple_arg(cmd->argv[0]);
	display_translation(2, "command.notfound", &args, 1);
	free_cmd(cmd, 1);
	cmd->imp->is_bquoted++;
	free_envp(cmd->envp, cmd->imp);
	free(cmd);
	exit(127);
}

void	execute_bin(t_cmd_params *cmd)
{
	char	*path;
	char	**argv;
	char	**envp_cpy;

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
