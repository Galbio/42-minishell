/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:05:06 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/12 14:25:33 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "regex.h"

static void	display_error(char code, char *name)
{
	if (!code)
	{
		translate(2, "command.toomanyargs", program_arg("exit", NULL), 1);
		return ;
	}
	translate(2, "command.numargrequired", program_arg("exit", new_arg(name, NULL)), 1);
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
		if (!get_depth(0))
		{
			free_readline();
			free_regex_items();
			free_translations();
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

	res = get_exit_status();
	av1 = cmd->argv[1] != NULL;
	if (!get_depth(0))
		translate(2, "exit", new_arg("", NULL), 1);
	if (!av1 || (parse_exit(cmd) == 1))
	{
		free_cmd(cmd, 1);
		free_envp(cmd->envp, cmd->imp);
		if (!get_depth(0))
		{
			free_readline();
			free_regex_items();
			free_translations();
		}
		free(cmd);
		if (!av1)
			exit(res);
		exit(2);
	}
	return (1);
}
