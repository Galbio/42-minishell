/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:25:11 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/13 02:32:52 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_error(char *s1, char *argv, char *s2, int res)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(s2, 2);
	return (res);
}
