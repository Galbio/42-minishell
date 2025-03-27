/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:51:10 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 16:05:17 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_special_char(char *str, t_int_tab *itab)
{
	if ((str[itab->i] == '\'') && (itab->cur_quote == '\''))
		return (itab->cur_quote = 0, 1);
	if (!itab->cur_quote && (str[itab->i] == '\'') && !itab->backslash)
		return (itab->cur_quote = '\'', 1);
	if (itab->cur_quote == '\'')
		return (0);
	if (!itab->backslash && (str[itab->i] == '\\')
		&& ft_strchr("$\"", str[itab->i + 1]))
		return (1);
	if (!itab->backslash && itab->cur_quote && (str[itab->i] == '\\')
		&& (str[itab->i + 1] == '\\'))
		return (1);
	if ((str[itab->i] == '"') && !itab->cur_quote && !itab->backslash)
		return (itab->cur_quote = '"', 1);
	if ((str[itab->i] == '"') && !itab->backslash)
		return (itab->cur_quote = 0, 1);
	return (0);
}
