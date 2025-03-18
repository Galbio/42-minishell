/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_var_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:06:57 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/18 01:36:29 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_to_var_end(char *str)
{
	int		i;
	int		pare_count;
	int		pare;

	i = 1;
	if (str[i] == '?')
		return (1);
	pare = str[i] == '(';
	pare_count = 0;
	while (str[i])
	{
		if (!pare && (str[i] != '_') && !ft_isalnum(str[i]))
			return (i);
		if (str[i] == '(')
			pare_count++;
		else if (str[i] == ')')
			pare_count--;
		if (pare && !pare_count)
			return (i + 1);
		i++;
	}
	return (i);
}
