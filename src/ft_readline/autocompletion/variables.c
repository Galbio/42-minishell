/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 23:21:38 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/11 23:29:21 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	add_variables_occurences(char *prefix, char *variable,
	t_array *occurences, int *size)
{
	int	local;
	int	i;

	local = variable[0] == '\\';
	if (!prefix[1]
		|| ft_strncmp(variable + local, prefix + 1, ft_strlen(prefix) - 1) == 0)
	{
		variable = ft_strjoin("$", variable + local);
		i = 0;
		while (variable[i] && variable[i] != '=')
			i++;
		if (variable[i] && variable[i + 1] && ft_isdir(variable + i + 1))
			variable[i++] = '/';
		variable[i] = '\0';
		add_and_sort_occurence(occurences, variable, size);
		free(variable);
	}
}
