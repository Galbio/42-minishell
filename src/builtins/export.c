/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:04:41 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/27 15:47:21 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_cor_char(char c, int fd)
{
	if (c == '"')
		write(fd, "\\\"", 2);
	else if (c == '\\')
		write(fd, "\\\\", 2);
	else if (c == '\n')
		write(fd, "\\n", 2);
	else if (c == '\t')
		write(fd, "\\t", 2);
	else if (c == '\v')
		write(fd, "\\v", 2);
	else if (c == '\r')
		write(fd, "\\r", 2);
	else if (c == '\f')
		write(fd, "\\f", 2);
	else
		write(fd, &c, 1);
}

void	write_vars(t_list *envp, int fd)
{
	char	*env;
	int		i;

	while (envp)
	{
		env = (char *)envp->content;
		ft_putstr_fd("declare -x ", fd);
		i = -1;
		while (env[++i] && env[i] != '=')
			write(fd, env + i, 1);
		if (!env)
			return ;
		write(fd, "=\"", 2);
		while (env[++i])
			write_cor_char(env[i], fd);
		write(fd, "\"\n", 2);
		envp = envp->next;
	}
}

char	*ft_export_vars(t_list *envp)
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
		(close(pipes[0]), write_vars(envp, pipes[1]));
		(close(pipes[1]), exit(0));
	}
	(close(pipes[1]), wait(NULL));
	dest = read_whole_fd(pipes[0]);
	close(pipes[0]);
	return (dest);
}

char	*add_envp(char *name, t_list **envp)
{
	const char	*var_name[3] = {NULL, NULL, NULL};
	int			i;

	i = -1;
	if (!name[0] || (name[0] == '=') || ft_isdigit(name[0]))
	{
		(ft_putstr_fd("bash: export: `", 2), ft_putstr_fd(name, 2));
		return (ft_putstr_fd("': not a valid identifier\n", 2), NULL);
	}
	while (name[++i])
	{
		if (name[i] == '=')
			break ;
		if ((name[i] != '_') && !ft_isalnum(name[i]))
		{
			(ft_putstr_fd("bash: export: `", 2), ft_putstr_fd(name, 2));
			return (ft_putstr_fd("': not a valid identifier\n", 2), NULL);
		}
	}
	if (name[i] != '=')
		return (NULL);
	var_name[1] = ft_substr(name, 0, i);
	ft_unset((char **)var_name, envp, NULL);
	ft_lstadd_back(envp, ft_lstnew(ft_strdup(name)));
	return (NULL);
}

char	*ft_export(char **argv, t_list **envp)
{
	int		i;

	if (!argv[1])
		return (ft_export_vars(*envp));
	i = 0;
	dest = NULL;
	while (argv[++i])
		add_envp(argv[i], envp);
	return (NULL);
}
