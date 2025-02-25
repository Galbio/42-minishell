/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:38:25 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/24 17:43:15 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcdup(char *str, char c)
{
	char	*dest;
	int		len;
	int		i;

	i = -1;
	len = 0;
	while (str[++i])
		if (str[i] == c)
			break ;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	dest[len] = 0;
	i = -1;
	while (++i < len)
		dest[i] = str[i];
	return (dest);
}
