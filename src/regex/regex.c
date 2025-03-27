/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:50:55 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/27 03:51:08 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	regex_match(char *text, char *pattern)
{
	int	n;
	int	m;
	int	i;
	int	j;
	int	start_index;
	int	match;

	n = ft_strlen(text);
	m = ft_strlen(pattern);
	i = 0;
	j = 0;
	start_index = -1;
	match = 0;
	while (i < n)
	{
		if (j < m && (pattern[j] == '?' || pattern[j] == text[i]))
		{
			i++;
			j++;
		}
		else if (j < m && pattern[j] == '*')
		{
			start_index = j;
			match = i;
			j++;
		}
		else if (start_index != -1)
		{
			j = start_index + 1;
			match++;
			i = match;
		}
		else
			return (0);
	}
	while (j < m && pattern[j] == '*')
		j++;
	return (j == m);
}
