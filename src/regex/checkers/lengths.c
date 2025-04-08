/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lengths.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:31:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/03 16:31:27 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

int	check_lengths(char *text, char *pattern)
{
	int	len;
	int	max;

	len = ft_strlen(text);
	if (len < min_value_len(pattern))
		return (0);
	max = max_value_len(pattern);
	if (max != -1 && len > max)
		return (0);
	return (1);
}
