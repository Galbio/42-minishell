/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_var_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:06:57 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/12 21:20:11 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	go_to_var_end(char *str, int *i)
{
	int		pare_count;

	if (str[*i + 1] != '(')
		return (0);
	*i += 2;
	pare_count = 1;
	while (pare_count && str[*i])
	{
		if (str[*i] == '(')
			pare_count++;
		else if (str[*i] == ')')
			pare_count--;
		(*i)++;
	}
	return (str[*i] == 0);
}
