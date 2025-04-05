/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:46:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/03 16:46:23 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

int	check_middle(char *text, char *pattern)
{
	int	start;
	int	next;
	int	pattern_start;
	int	next_p;

	pattern_start = 0;
	start = 0;
	while (ft_strlen(pattern + pattern_start) > 0)
	{
		if (ft_strlen(pattern + pattern_start) == 1
			&& (pattern + pattern_start)[0] == '*')
			return (1);
		next = find_first_occurrence(text + start,
				pattern + pattern_start, &next_p);
		pattern_start += next_p + 1;
		if (next == -1)
			return (0);
		start += (next);
	}
	return (1);
}
