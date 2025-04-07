/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_return.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:53:40 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/07 23:14:39 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_end_newlines(char *str)
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
	dest[len] = 0;
	while (--len >= 0)
		dest[len] = str[len];
	free(str);
	return (dest);
}

static int	get_return_size(char *str, char quote)
{
	int		ret;
	int		i;

	ret = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\\')
			ret++;
		else if (quote && ft_strchr(" \n\t", str[i]))
			ret++;
	}
	return (ret + i);
}

char	*parse_var_return(char *str, char quote)
{
	char	*dest;
	int		ret;
	int		i;

	str = remove_end_newlines(str);
	ret = get_return_size(str, quote);
	dest = malloc(sizeof(char) * (ret + 1));
	if (!dest)
		return (NULL);
	ret = 0;
	i = -1;
	while (str[++i])
	{
		if ((str[i] == '\\') || (quote && ft_strchr(" \t\n", str[i])))
			dest[ret++] = '\\';
		dest[ret++] = str[i];
	}
	dest[ret] = 0;
	free(str);
	return (dest);
}
