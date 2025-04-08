/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_quote_parser.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:16:35 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/08 15:09:23 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_parsed_size(char *str)
{
	int		i;
	int		res;

	res = 0;
	i = -1;
	while (str[++i])
	{
		res += (str[i] == '"') || ((str[i] == '\\') && (str[i + 1] != '$'));
		res++;
	}
	return (res);
}

char	*parse_heredoc_quote(char *str)
{
	char	*dest;
	int		len;
	int		i;
	int		ret;

	if (!str)
		return (ft_strdup("\"\""));
	len = get_parsed_size(str);
	dest = malloc(sizeof(char) + (len + 3));
	if (!dest)
		return (NULL);
	i = -1;
	ret = 1;
	dest[0] = '"';
	while (str[++i])
	{
		if ((str[i] == '"') || ((str[i] == '\\') && (str[i + 1] != '$')))
			dest[ret++] = '\\';
		dest[ret++] = str[i];
	}
	dest[len + 1] = '"';
	dest[len + 2] = 0;
	return (dest);
}
