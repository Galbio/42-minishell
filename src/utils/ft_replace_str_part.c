/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_str_part.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 02:01:02 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/02 00:38:59 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace_str_part(char *src, int start, int replace_len,
		char *to_add)
{
	char	*dest;
	int		len;
	int		to_add_len;

	len = ft_strlen(src);
	to_add_len = ft_strlen(to_add);
	dest = malloc(sizeof(char) * (len - replace_len + to_add_len + 1));
	if (!dest)
		return (NULL);
	ft_memcpy(dest, src, start);
	ft_memcpy(dest + start, to_add, to_add_len);
	ft_memcpy(dest + start + to_add_len, src + start + replace_len,
		len - (start + replace_len));
	dest[len - replace_len + to_add_len] = 0;
	return (dest);
}
