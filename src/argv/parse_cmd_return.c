/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_return.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:53:40 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/13 18:18:09 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_var_return(char *str)
{
	int		len;
	char	*dest;

	len = ft_strlen(str);
	while (--len >= 0)
		if (str[len] != '\n')
			break ;
	len++;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	ft_memcpy(dest, str, len);
	dest[len] = 0;
	free(str);
	return (dest);
}
