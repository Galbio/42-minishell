/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:05:06 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/13 19:57:10 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "regex.h"

static char	check_exit_error(char **argv)
{
	int		i;

	i = -1;
	if ((argv[1][0] == '-') && !ft_isdigit(argv[1][1]))
		return (display_error("minishell: exit: ", argv[1],
				": numeric argument required\n", 1));
	else if (argv[1][0] == '-' || argv[1][0] == '+')
		i++;
	while (argv[1][++i])
	{
		if (!ft_isdigit(argv[1][i]))
			return (display_error("minishell: exit: ", argv[1],
					": numeric argument required\n", 1));
	}
	if (argv[2])
		return (display_error("minishell: exit: too many arguments\n",
				"", "", 0));
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
	if (!get_depth(0) && isatty(STDIN_FILENO))
		write(STDERR_FILENO, "exit\n", 5);
	if (!av1 || (parse_exit(cmd) == 1))
	{
		free_cmd(cmd, 1);
		free_envp(cmd->envp, cmd->imp);
		if (!get_depth(0))
		{
			free_readline();
			free_regex_items();
		}
		free(cmd);
		if (!av1)
			exit(res);
		exit(2);
	}
	return (1);
}
