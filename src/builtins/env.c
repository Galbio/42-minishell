/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:11:56 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/13 23:10:21 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	check_error(char **argv)
{
	int		i;

	i = 0;
	while (argv[++i])
	{
		if (!ft_strchr(argv[i], '='))
		{
			ft_putstr_fd("env: ‘", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("’: No such file or directory", 2);
			return (1);
		}
	}
	return (0);
}

int	ms_env(t_cmd_params *cmd)
{
	t_list	*cur;
	char	*temp;
	int		i;

	if (cmd->argv[1] && check_error(cmd->argv))
	{
		write(1, "\n", 1);
		return (127);
	}
	cur = *(cmd->envp);
	while (cur)
	{
		temp = (char *)cur->content;
		write(1, temp, ft_securelen(temp));
		write(1, "\n", 1);
		cur = cur->next;
	}
	i = 0;
	while (cmd->argv[++i])
	{
		write(1, cmd->argv[i], ft_strlen(cmd->argv[i]));
		write(1, "\n", 1);
	}
	return (0);
}
