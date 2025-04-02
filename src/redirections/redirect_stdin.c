/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_stdin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 00:17:28 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/02 02:01:32 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	init_herefiles(char *filename, int pipes[2], int *fd)
{
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
	{
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	if (pipe(pipes))
	{
		close(*fd);
		return (1);
	}
	return (0);
}

static char	redirect_herefile(char *filename, t_cmd_params *cmd)
{
	int		fd;
	int		pipes[2];
	char	*tmp;

	if (init_herefiles(filename, pipes, &fd))
		return (1);
	if (ZSH && cmd->imp->input_fd)
	{
		tmp = ft_get_contents(cmd->imp->input_fd);
		write(pipes[1], tmp, ft_strlen(tmp));
		free(tmp);
	}
	tmp = ft_get_contents(fd);
	write(pipes[1], tmp, ft_strlen(tmp));
	free(tmp);
	close(pipes[1]);
	close(fd);
	dup2(pipes[0], 0);
	if (cmd->imp->input_fd)
		close(cmd->imp->input_fd);
	cmd->imp->input_fd = pipes[0];
	return (0);
}

static char	redirect_herestring(char *value, t_cmd_params *cmd, char is_heredoc)
{
	int		pipes[2];
	char	*old;

	if (pipe(pipes) < 0)
		return (1);
	if (ZSH && cmd->imp->input_fd)
	{
		old = ft_get_contents(cmd->imp->input_fd);
		write(pipes[1], old, ft_strlen(old));
		free(old);
	}
	write(pipes[1], value, ft_strlen(value));
	if (!is_heredoc)
		write(pipes[1], "\n", 1);
	close(pipes[1]);
	dup2(pipes[0], 0);
	if (cmd->imp->input_fd)
		close(cmd->imp->input_fd);
	cmd->imp->input_fd = pipes[0];
	return (0);
}

static char	redirect_stdin(char *method, char **value, t_cmd_params *cmd)
{
	int		len;

	len = ft_strlen(method);
	if (len == 1)
	{
		if (redirect_herefile(value[1], cmd))
			return (1);
	}
	else if ((len == 3) && (method[2] == '<'))
	{
		if (redirect_herestring(value[1], cmd, 0))
			return (1);
	}
	else
		if (redirect_herestring(value[1], cmd, 1))
			return (1);
	return (0);
}

char	handle_redirections(t_cmd_params *cmd)
{
	t_list	*cur;
	char	*ret;
	int		i;

	cur = cmd->redir;
	while (cur)
	{
		ret = (char *)cur->content;
		if (!cur->next)
			return (free_redir(cmd->redir, 1));
		i = 0;
		while (!ft_strchr("<>", ret[i]))
			i++;
		if (ret[i] == '<')
		{
			if (redirect_stdin(ret, cur->next->content, cmd))
				return (free_redir(cmd->redir, 1));
		}
		else if (ret[i] == '>')
			if (redirect_stdout(ret, cur->next->content))
				return (free_redir(cmd->redir, 1));
		cur = cur->next->next;
	}
	return (free_redir(cmd->redir, 0));
}
