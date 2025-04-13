/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:09:48 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/14 01:00:24 by lroussel         ###   ########.fr       */
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

	if (ft_isdir(str))
		return (NULL);
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

static void	display_errors(int is_env, char *command, int *code,
	t_main_envp *imp)
{
	char	*similar;
	char	*slash;
	int		res;

	slash = ft_strchr(command, '/');
	if (!is_env && ft_isdir(command) && slash)
	{
		display_error("minishell: ", command, ": Is a directory\n", 0);
		*code = 126;
	}
	else if (!is_env && (!imp->path || slash))
	{
		res = command_path_errors(command, 0);
		if (res == 2)
			*code = 126;
	}
	else if (!is_env)
	{
		similar = get_similar_commands(command);
		ft_putstr_fd(similar, 2);
		free(similar);
	}
	else
		env_errors(command);
}

static void	cmd_not_found(t_cmd_params *cmd, int is_env)
{
	int		code;

	code = 127;
	display_errors(is_env, cmd->argv[0], &code, cmd->imp);
	free_cmd(cmd, 1);
	free_envp(cmd->envp, cmd->imp);
	free(cmd);
	exit(code);
}

void	execute_bin(t_cmd_params *cmd, int is_env)
{
	char	*path;
	char	**argv;
	char	**envp_cpy;
	int		i;

	get_depth(-1);
	path = get_command_path(cmd->argv[0], cmd->imp->path);
	if (!path)
		cmd_not_found(cmd, is_env);
	argv = cmd->argv;
	envp_cpy = create_envp_cpy(cmd->envp, cmd->imp);
	free_cmd(cmd, 'b');
	free_envp(cmd->envp, cmd->imp);
	free(cmd);
	execve(path, argv, envp_cpy);
	i = -1;
	while (envp_cpy[++i])
		free(envp_cpy[i]);
	free(envp_cpy);
	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
	free(path);
	exit(1);
}
