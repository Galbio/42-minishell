/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bquotes_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 22:12:44 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 08:21:01 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_bquoted_size(char *src)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (src[++itab.i])
	{
		itab.backslash = itab.i && (src[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(src, &itab);
		if ((src[itab.i] == '`') && !itab.backslash && (itab.cur_quote != '\''))
			itab.ret = !itab.ret;
		if ((src[itab.i] == '`') && !itab.backslash
			&& itab.ret && (itab.cur_quote != '\''))
			itab.res++;
		itab.res++;
	}
	return (itab.res);
}

char	*handle_bquotes(char *src)
{
	t_int_tab	itab;
	char		*dest;

	itab = init_int_tab();
	dest = malloc(sizeof(char) * (get_bquoted_size(src) + 1));
	if (!dest)
		return (NULL);
	while (src[++itab.i])
	{
		itab.backslash = itab.i && (src[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(src, &itab);
		if ((src[itab.i] == '`') && !itab.backslash && (itab.cur_quote != '\''))
			itab.ret = !itab.ret;
		if ((src[itab.i] == '`') && itab.ret
			&& !itab.backslash && (itab.cur_quote != '\''))
			dest[itab.res++] = '$';
		if ((src[itab.i] == '`') && !itab.backslash && (itab.cur_quote != '\''))
			dest[itab.res++] = ")("[itab.ret];
		else
			dest[itab.res++] = src[itab.i];
	}
	dest[itab.res] = 0;
	free(src);
	return (dest);
}
