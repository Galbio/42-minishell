/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:09:48 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/25 00:47:16 by gakarbou         ###   ########.fr       */
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

static char	handle_redirections(t_cmd_params *cmd)
{
	t_list	*cur;
	char	*ret;
	int		i;

	if (!cmd->redir)
		return (0);
	cur = cmd->redir;
	while (cur)
	{
		ret = (char *)cur->content;
		if (!cur->next)
			return (1);
		i = 0;
		while (!ft_strchr("<>", ret[i]))
			i++;
		if (ret[i] == '<')
			if (redirect_stdin(ret, cur->next->content, cmd))
				return (1);
		cur = cur->next->next;
	}
	return (0);
}

void	execute_bin(t_cmd_params *cmd)
{
	char	*path;

	path = get_command_path(cmd->argv[0], cmd->imp->path);
	if (!path)
	{
		if (!cmd->imp->path)
			ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (handle_redirections(cmd))
		exit(1);
	execve(path, cmd->argv, cmd->imp->envp_cpy);
}
