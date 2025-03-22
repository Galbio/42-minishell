/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_whitespaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:02:29 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/18 21:39:11 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	end_ws_streak(char *str, int len)
{
	int		i;

	i = len - 1;
	while (1)
	{
		if (ft_strchr(" \n\t", str[i]))
		{
			if (!i)
				return (len);
			if (str[i - 1] == '\\')
				return (i + 1);
			i--;
		}
		else
			break ;
	}
	return (i + 1);
}

char	*trim_ws(char *str)
{
	char	*dest;
	int		i;
	int		ret;
	int		len;

	i = 0;
	while (ft_strchr(" \n\t", str[i]))
		i++;
	len = ft_strlen(str + i);
	len = end_ws_streak(str + i, len);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	ret = 0;
	while (--len >= 0)
	{
		dest[ret] = str[i + ret];
		ret++;
	}
	dest[ret] = 0;
	free(str);
	return (dest);
}
