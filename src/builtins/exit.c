/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:05:06 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/26 19:25:34 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_str(char *command)
{
	t_int_tab	tabe;

	ft_putstr_fd("minishell: exit: ", 2);
	tabe = init_int_tab();
	while (command[++tabe.i])
	{
		if ((command[tabe.i] == 32) && !tabe.cur_quote)
			break ;
		check_special_char(command[tabe.i], &tabe.backslash, &tabe.cur_quote);
		write(2, command + tabe.i, 1);
	}
	free(command - 5);
	ft_putstr_fd(": numeric argument required\n", 2);
}

char	check_exit_errors(char **argv)
{
	t_int_tab	tabe;

	tabe = init_int_tab();
	if ((argv[1][0] == '-') && !ft_isdigit(argv[1][1]))
	{
		(ft_putstr_fd("minishell: exit: ", 2), ft_putstr_fd(argv[1], 2));
		return (ft_putstr_fd(": numeric argument required\n", 2), 1);
	}
	else if (argv[1][0] == '-')
		tabe.i++;
	while (argv[1][++tabe.i])
	{
		if (!ft_isdigit(argv[1][tabe.i]))
		{
			(ft_putstr_fd("minishell: exit: ", 2), ft_putstr_fd(argv[1], 2));
			return (ft_putstr_fd(": numeric argument required\n", 2), 1);
		}
	}
	if (argv[2])
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 0);
	exit((unsigned char)ft_atoi(argv[1]));
	return (0);
}

char	*ft_exit(char **argv)
{
	write(2, "exit\n", 5);
	if (!argv[1])
		exit(0);
	if (check_exit_errors(argv) == 1)
		exit(2);
	return (NULL);
}
