/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:57:44 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/31 15:57:55 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

int	min_value_len(char *pattern)
{
	int	i;
	int	min_len;
	char	*brackets;

	i = 0;
	min_len = 0;
	while (pattern[i])
	{
		if (pattern[i] != '*')
		{
			brackets = find_brackets(pattern + i);
			if (brackets)
				i += ft_strlen(brackets) - 1;
			min_len++;
		}
		i++;
	}
	return (min_len);
}

int	max_value_len(char *pattern)
{
	if (ft_strchr(pattern, '*'))
		return (-1);
	return (min_value_len(pattern));
}
