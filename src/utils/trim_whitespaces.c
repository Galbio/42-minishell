/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_whitespaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:02:29 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 04:57:59 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	end_ws_streak(char *str, int len)
{
	int		i;

	i = len - 1;
	while (1)
	{
		if (str[i] && ft_strchr(" \n\t", str[i]))
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

static char	*fill_dest(char *str, int len, int i)
{
	char	*dest;
	int		ret;

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

char	*trim_ws(char *str)
{
	int		i;
	int		len;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && ft_strchr(" \n\t", str[i]))
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	len = end_ws_streak(str + i, ft_strlen(str + i));
	return (fill_dest(str, len, i));
}
