/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:51:10 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/28 18:00:33 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_special_char(char c, char *backslash, char *cur_quote)
{
	if ((c == '\'') && (*cur_quote == '\''))
		return (*cur_quote = 0, 0);
	else if ((*cur_quote == 0) && (c == '\'') && (*backslash == 0))
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
	else if (c != '$')
		*backslash = 0;
	return (1);
}
