/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bquotes_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 22:12:44 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/03 14:35:09 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_bquoted_size(char *res)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (res[++itab.i])
	{
		if (res[itab.i] == '`')
			itab.ret = 1 - (itab.ret % 2);
		if ((res[itab.i] == '`') && itab.backslash && itab.ret)
			itab.res++;
		if ((res[itab.i] == '\\') && !itab.backslash)
			itab.backslash = 1;
		else if (res[itab.i] == '\\')
			itab.backslash = 0;
		itab.res++;
	}
	return (itab.res);
}

char	*handle_bquotes(char *res)
{
	t_int_tab	itab;
	char		*dest;

	itab = init_int_tab();
	dest = malloc(sizeof(char) * (get_bquoted_size(res) + 1));
	if (!dest)
		return (NULL);
	while (res[++itab.i])
	{
		if ((res[itab.i] == '`') && !itab.backslash)
			itab.ret = 1 - (itab.ret % 2);
		if ((res[itab.i] == '`') && itab.ret && !itab.backslash)
			dest[itab.res++] = '$';
		if ((res[itab.i] == '\\') && !itab.backslash)
			itab.backslash = 1;
		else if (res[itab.i] == '\\')
			itab.backslash = 0;
		if ((res[itab.i] == '`') && !itab.backslash)
			dest[itab.res++] = ")("[itab.ret];
		else
			dest[itab.res++] = res[itab.i];
	}
	dest[itab.res] = 0;
	free(res);
	return (dest);
}
