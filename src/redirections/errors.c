/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:04:14 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/13 02:44:59 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_file_errors(char **values, char *og_str)
{
	if (values[1])
	{
		write(2, "minishell: ", 11);
		ft_putstr_fd(og_str, 2);
		write(2, ": ambiguous redirect\n", 21);
		return (1);
	}
	if (ft_strlen(values[0]) > 255)
	{
		write(2, "minishell: ", 11);
		ft_putstr_fd(values[0], 2);
		write(2, ": File name too long\n", 21);
		return (1);
	}
	if (ft_isdir(values[0]))
	{
		write(2, "minishell: ", 11);
		ft_putstr_fd(values[0], 2);
		write(2, ": Is a directory\n", 17);
		return (1);
	}
	return (0);
}
