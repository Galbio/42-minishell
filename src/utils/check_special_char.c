/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:51:10 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/20 21:02:34 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	check_other_special_char(char *str, t_int_tab *itab)
{
	if (itab->backslash && !itab->cur_quote && ft_strchr("\\$\"", str[itab->i]))
		return (0);
	if (itab->backslash && !itab->cur_quote)
		return (itab->backslash = 0, 0);
	if ((str[itab->i] == '"') && !itab->cur_quote && !itab->backslash)
		return (itab->cur_quote = '"', 1);
	if ((str[itab->i] == '"') && !itab->backslash)
		return (itab->cur_quote = 0, 1);
	return (0);
}

char	check_special_char(char *str, t_int_tab *itab)
{
	if ((str[itab->i] == '\'') && (itab->cur_quote == '\''))
		return (itab->cur_quote = 0, 1);
	if (!itab->cur_quote && (str[itab->i] == '\'') && !itab->backslash)
		return (itab->cur_quote = '\'', 1);
	if (itab->cur_quote == '\'')
		return (0);
	if (itab->backslash && !itab->cur_quote && (str[itab->i] == '\\')
		&& (str[itab->i + 1] == '\\'))
		return (itab->backslash = 0, 1);
	if (!itab->backslash && (str[itab->i] == '\\') && !itab->cur_quote
		&& ft_strchr(" \n\t\\", str[itab->i + 1]))
		return (itab->backslash = 1, 0);
	if (!itab->backslash && (str[itab->i] == '\\') && !itab->cur_quote)
		return (itab->backslash = 1, 1);
	if (!itab->backslash && (str[itab->i] == '\\')
		&& ft_strchr("$\\\"", str[itab->i + 1]))
		return (itab->backslash = 1, 1);
	if (itab->backslash && !itab->cur_quote && ft_strchr(" \n\t", str[itab->i])
		&& (itab->i && str[itab->i - 1] == '\\'))
		return (0);
	return (check_other_special_char(str, itab));
}
