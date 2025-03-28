/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:52:12 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/28 14:26:38 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	update_quotes(char *cur_quote, char *backslash, char c)
{
	if (*backslash && (*cur_quote == '\''))
		*backslash = 0;
	if ((c == '\'') && (*cur_quote == '\''))
		*cur_quote = 0;
	else if ((c == '"') && (*cur_quote == '"') && (*backslash == 0))
		*cur_quote = 0;
	else if ((*backslash == 0) && (*cur_quote == 0) && ft_strchr("\"'", c))
		*cur_quote = c;
}

static char	find_delim(char *build)
{
	int		i;
	char	cur_quote;
	char	backslash;
	char	ignore_tab;

	const char *delim = "EOF";
	const int len = ft_strlen(delim);
	i = -1;
	cur_quote = 0;
	backslash = 0;
	ignore_tab = build[2] == '-';
	while (build[++i])
	{
		backslash = i && (build[i -1] == '\\') && !backslash;
		update_quotes(&cur_quote, &backslash, build[i]);
		while (!backslash && !cur_quote && (build[i] == '\n'))
		{
			i++;
			if (!build[i])
				return (0);
			while (ignore_tab && (build[i] == '\t'))
				i++;
			if ((build[i + len] == '\n') && !ft_strncmp(delim, build + i, len))
				return (1);
			while (build[i] != '\n')
				i++;
		}
	}
	return (0);
}

int	check_heredoc(char *build)
{
	int		i;
	char	cur_quote;
	char	backslash;

	i = -1;
	cur_quote = 0;
	backslash = 0;
	while (build[++i])
	{
		backslash = i && (build[i -1] == '\\') && !backslash;
		update_quotes(&cur_quote, &backslash, build[i]);
		if (!backslash && !cur_quote && !ft_strncmp("<<", build + i, 2) &&
				ft_strchr(" \t-", build[i + 1]))
			if (!find_delim(build + i))
				return (0);
	}
	return (1);
}
