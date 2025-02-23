/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_securejoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 06:23:04 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/23 21:19:13 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_securejoin(char *s1, char *s2, char must_free)
{
	size_t	i;
	size_t	j;
	char	*dest;

	dest = malloc((1 + ft_securelen(s1) + ft_securelen(s2)) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	if (must_free && s1)
		free((void *)s1);
	j = 0;
	while (s2 && s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = 0;
	return (dest);
}
