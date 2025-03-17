/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:05:06 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/13 23:35:54 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	check_exit_errors(char **argv)
{
	t_int_tab	itab;

	itab = init_int_tab();
	if ((argv[1][0] == '-') && !ft_isdigit(argv[1][1]))
	{
		display_error(1, argv[1]);
		return (1);
	}
	else if (argv[1][0] == '-')
		itab.i++;
	while (argv[1][++itab.i])
	{
		if (!ft_isdigit(argv[1][itab.i]))
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
	exit(ft_atoi(argv[1]));
	return (0);
}

int	ms_exit(t_cmd_params *cmd)
{
	if (!cmd->imp->is_bquoted)
		write(2, "exit\n", 5);
	if (!cmd->argv[1])
		exit(0);
	if (check_exit_errors(cmd->argv) == 1)
		exit(2);
	return (0);
}
