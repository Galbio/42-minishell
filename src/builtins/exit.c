/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:05:06 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/24 19:15:58 by gakarbou         ###   ########.fr       */
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

char	check_exit_errors(char *command)
{
	t_int_tab	tabe;

	tabe = init_int_tab();
	while (command[++tabe.i])
	{
		if ((command[tabe.i] == 32) && !tabe.cur_quote)
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		if ((command[tabe.i] == 32) && !tabe.cur_quote)
			return (0);
		if (!ft_isdigit(command[tabe.i]) || (!tabe.i && command[tabe.i] == '-'))
			return (ft_exit_str(command), exit(2), 1);
	}
	tabe.ret = ft_atoi(command);
	free(command - 5);
	exit((unsigned char)tabe.ret);
	return (0);
}

char	*ft_exit(char *command)
{
	write(2, "exit\n", 5);
	if (command[4] == 0)
		(free(command), exit(0));
	command += 5;
	if (check_exit_errors(command) == 1)
		(free(command - 5), exit(2));
	free(command - 5);
	return (NULL);
}
