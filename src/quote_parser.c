/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:21:54 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/22 23:36:44 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_special_char(char c, char *backslash, char *cur_quote)
{
	if ((c == '\'') && (*cur_quote == '\''))
		return (*cur_quote = 0, 0);
	else if ((*cur_quote == 0) && (c == '\''))
		return (*cur_quote = '\'', 0);
	else if (*cur_quote == '\'')
		return (1);
	else if ((c == '"') && (*cur_quote == '"') && (*backslash))
		return (*backslash = 0, 1);
	else if ((c == '"') && (*cur_quote == '"'))
		return (*cur_quote = 0, 0);
	else if ((*cur_quote == 0) && (c == '"'))
		return (*cur_quote = '"', 0);
	else if (c == '"')
		return (*cur_quote = '"', 0);
	if ((c == '\\') && (*backslash))
		return (*backslash = 0, 1);
	else if (c == '\\')
		return (*backslash = 1, 0);
	else
		*backslash = 0;
	return (1);
}

int	get_parsed_len(char *str)
{
	char	back_slashed;
	char	cur_quote;
	int		res;
	int		i;

	i = -1;
	res = 0;
	cur_quote = 0;
	back_slashed = 0;
	while (str[++i])
	{
		if (!check_special_char(str[i], &back_slashed, &cur_quote))
			continue ;
		res++;
	}
	return (res);
}

char	*parse_quotes(char *str, int i)
{
	char	back_slashed;
	char	*dest;
	char	cur_quote;
	int		res;

	dest = malloc(sizeof(char) * (get_parsed_len(str, -1)));
	if (!dest)
		return (NULL);
	res = 0;
	cur_quote = 0;
	back_slashed = 0;
	while (str[++i])
	{
		if (!check_special_char(str[i], &back_slashed, &cur_quote))
			continue ;
		dest[res++] = str[i];
	}
	dest[res] = 0;
	return (dest);
}
