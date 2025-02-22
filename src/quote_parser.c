/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:21:54 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/22 22:38:10 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	check_special_char(char c, char *backslash, char *cur_quote)
{
	if ((c == '"') && (*cur_quote == '\''))
		 return (1);
	else if ((c == '"') && (*cur_quote == '"') && (*backslash))
		return (0);
	else if ((c == '"') && (*cur_quote == '"'))
		 *cur_quote = 0;
	else if ((c == '\'') && (*cur_quote == '\''))
		*cur_quote = 0;
	else if ((*cur_quote == 0) && (c == '"'))
		*cur_quote = '"';
	else if ((*cur_quote == 0) && (c == '\''))
		*cur_quote = '\'';
	else if (c == '"')
		*cur_quote = '"';
	else
		return (1);
	if ((c == '\\') && (*backslash))
		return (*backslash = 0, 1);
	else if (c == '\\')
		return (*backslash = 1, 0);
	else
		*backslash = 0;
	return (0);
}

int		get_parsed_len(char *str, int len)
{
	char	back_slashed;
	char	cur_quote;
	int		res;
	int		i;

	i = -1;
	res = 0;
	cur_quote = 0;
	while (str[++i])
	{
		if (!check_special_char(str[i], &back_slashed, &cur_quote))
			continue ;
		res++;
	}
	return (res);
}

char	*parse_quotes(char *str)
{
	char	*dest;

	printf("%d\n", get_parsed_len(str, ft_strlen(str)));
	exit(0);
	dest = malloc(sizeof(char) * (get_parsed_len(str, ft_strlen(str)) + 1));
}

int	main(int argc, char **argv)
{
	char	*nice;

	nice = readline("");
	printf("Og = %s\n", nice);
	parse_quotes(nice);
	return (0);
}
