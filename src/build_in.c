/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:22:59 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/23 16:31:36 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	built_in_compare(char *name)
{
	if (!ft_strncmp(name, "echo", 5))
		return (free(name), 1);
	else if (!ft_strncmp(name, "cd", 3))
		return (free(name), 2);
	else if (!ft_strncmp(name, "pwd", 4))
		return (free(name), 3);
	else if (!ft_strncmp(name, "export", 7))
		return (free(name), 4);
	else if (!ft_strncmp(name, "unset", 6))
		return (free(name), 5);
	else if (!ft_strncmp(name, "env", 4))
		return (free(name), 6);
	else if (!ft_strncmp(name, "exit", 5))
		return (free(name), 7);
	return (free(name), 0);
}

char	check_built_in(char **name)
{
	int			len;
	t_int_tab	tabe;
	char		*command_name;
	char		*temp;

	len = ft_securelen(name[0]);
	tabe = init_int_tab();
	while (name[0][++tabe.i])
	{
		if ((name[0][tabe.i] == 32) && (!tabe.cur_quote))
			break ;
		check_special_char(name[0][tabe.i], &tabe.backslash, &tabe.cur_quote);
	}
	command_name = ft_substr(name[0], 0, tabe.i);
	temp = ft_strrchr(command_name, '/');
	if (!temp)
		return (built_in_compare(command_name));
	return (built_in_compare(ft_strdup(temp + 1)));
}
