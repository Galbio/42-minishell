/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:25:11 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/14 02:06:42 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*early_heredoc(char *str, int cmd_count, char *res)
{
	write(2, "\nminishell: warning: here-document at line ", 43);
	ft_putnbr_fd(cmd_count, 2);
	write(2, " delimited by end-of-file (wanted `", 35);
	ft_putstr_fd(str, 2);
	write(2, "')\n", 3);
	return (res);
}

int	display_error(char *s1, char *argv, char *s2, int res)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(s2, 2);
	return (res);
}
