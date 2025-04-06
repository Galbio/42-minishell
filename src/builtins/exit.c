/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:05:06 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/04 10:41:12 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "regex.h"

static void	display_error(char code, char *name)
{
	if (!code)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": numertic argument required\n", 2);
}

static char	check_exit_error(char **argv)
{
	int		i;

	i = -1;
	if ((argv[1][0] == '-') && !ft_isdigit(argv[1][1]))
	{
		display_error(1, argv[1]);
		return (1);
	}
	else if (argv[1][0] == '-')
		i++;
	while (argv[1][++i])
	{
		if (!ft_isdigit(argv[1][i]))
		{
			display_error(1, argv[1]);
			return (1);
		}
	}
	if (argv[2])
	{
		display_error(0, NULL);
		return (0);
	}
	return (2);
}

static char	parse_exit(t_cmd_params *cmd)
{
	int		res;

	res = check_exit_error(cmd->argv);
	if (!res)
		return (0);
	if (res == 2)
	{
		res = ft_atoi(cmd->argv[1]);
		free_cmd(cmd, 1);
		free_envp(cmd->envp, cmd->imp);
		if (!cmd->imp->is_bquoted)
		{
			free_readline_main();
			free_regex_items();
		}
		free(cmd);
		exit(res);
	}
	return (1);
}

int	ms_exit(t_cmd_params *cmd)
{
	int		res;
	char	av1;

	res = cmd->imp->exit_status;
	av1 = cmd->argv[1] != NULL;
	if (!cmd->imp->is_bquoted)
		write(2, "exit\n", 5);
	if (!av1 || (parse_exit(cmd) == 1))
	{
		free_cmd(cmd, 1);
		free_envp(cmd->envp, cmd->imp);
		if (!cmd->imp->is_bquoted)
		{
			free_readline_main();
			free_regex_items();
		}
		free(cmd);
		if (!av1)
			exit(res);
		exit(2);
	}
	return (1);
}
