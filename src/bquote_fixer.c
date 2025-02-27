/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bquote_fixer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:22:29 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/27 21:45:38 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_cleaned_size(char *str)
{
	int		len;
	int		i;

	len = 0;
	i = -1;
	while (str[++i])
	{
		if (ft_iswhitespace(str[i]))
		{
			len++;
			while (ft_iswhitespace(str[i]))
				i++;
			i--;
		}
		else
			len++;
	}
	return (len);
}

static char	only_ws_left(char *str)
{
	while (*str)
	{
		if (!ft_iswhitespace(*str))
			return (0);
		str++;
	}
	return (1);
}

char	*clean_whitespaces(char *str)
{
	t_int_tab	itab;
	char		*dest;

	itab = init_int_tab();
	dest = malloc(sizeof(char) * (get_cleaned_size(str) + 1));
	if (!dest)
		return (NULL);
	while (str[++itab.i])
	{
		if (ft_iswhitespace(str[itab.i]))
		{
			if (only_ws_left(str + itab.i))
				break ;
			dest[itab.ret++] = 32;
			while (ft_iswhitespace(str[itab.i]))
				itab.i++;
			itab.i--;
		}
		else
			dest[itab.ret++] = str[itab.i];
	}
	dest[itab.ret] = 0;
	free(str);
	return (dest);
}
