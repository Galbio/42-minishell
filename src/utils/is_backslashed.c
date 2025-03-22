/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_backslashed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 01:07:42 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/22 01:15:22 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_backslashed(char *str, int i)
{
	char	res;

	res = 0;
	while (--i >= 0)
	{
		if (str[i] != '\\')
			break ;
		res = !res;
	}
	return (res);
}
