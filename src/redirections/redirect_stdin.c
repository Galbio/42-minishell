/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_stdin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 00:17:28 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/12 17:14:20 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	init_herefiles(t_redirection *redir, int pipes[2], int *fd)
{
	if (pipe(pipes))
		return (1);
	if (redirection_file_errors(redir->values, redir->og_str))
		return (1);
	*fd = open(redir->values[0], O_RDONLY);
	if (*fd < 0)
	{
		write(2, "minishell: ", 11);
		write(2, redir->values[0], ft_strlen(redir->values[0]));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	return (0);
}

static char	redirect_herefile(t_redirection *redir, t_cmd_params *cmd)
{
	int		fd;
	int		pipes[2];
	char	*tmp;

	if (init_herefiles(redir, pipes, &fd))
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

static char	redirect_herestring(char *value, t_cmd_params *cmd, int is_heredoc)
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

static char	redirect_stdin(t_redirection *redir, t_cmd_params *cmd)
{
	int		len;

	len = ft_strlen(redir->method);
	if (len == 1)
		return (redirect_herefile(redir, cmd));
	else if ((len == 3) && (redir->method[2] == '<'))
		return (redirect_herestring(redir->values[0], cmd, 0));
	return (redirect_herestring(redir->values[0], cmd, 1));
}

char	handle_redirections(t_cmd_params *cmd)
{
	t_list			*cur;
	t_redirection	*ret;
	int				i;

	cur = cmd->redir;
	while (cur)
	{
		ret = cur->content;
		if (!ret->values[0])
			return (free_redir(cmd->redir, 1));
		i = 0;
		while (!ft_strchr("<>", ret->method[i]))
			i++;
		if (ret->method[i] == '<')
		{
			if (redirect_stdin(ret, cmd))
				return (free_redir(cmd->redir, 1));
		}
		else if (ret->method[i] == '>')
			if (redirect_stdout(ret))
				return (free_redir(cmd->redir, 1));
		cur = cur->next;
	}
	return (free_redir(cmd->redir, 0));
}
