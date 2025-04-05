/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:50:55 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/04 12:52:46 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

static int	exit_regex(char *v, char *pat, int res)
{
	free(v);
	free(pat);
	return (res);
}

int	regex_match(char *text, char *pattern)
{
	int		len;

	if (!check_lengths(text, pattern))
		return (0);
	text = ft_strdup(text);
	pattern = ft_strdup(pattern);
	if (pattern[0] != '*' && !check_beginning(&text, &pattern))
		return (exit_regex(text, pattern, 0));
	if (pattern[ft_strlen(pattern)] != '*' && !check_end(&text, &pattern))
		return (exit_regex(text, pattern, 0));
	clean_pattern(&pattern);
	len = ft_strlen(pattern);
	if ((len == 1 && pattern[0] == '*') || (len == 0 && ft_strlen(text) == 0))
		return (exit_regex(text, pattern, 1));
	if (pattern[len - 1] == '*')
		pattern[len - 1] = '\0';
	return (exit_regex(text, pattern, check_middle(text, pattern + 1)));
}
