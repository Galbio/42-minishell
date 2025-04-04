/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_subcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:59:06 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/04 13:59:24 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_subshell(char *str)
{
	t_int_tab	itab;
	char		*dest;

	itab = init_int_tab();
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(str, &itab);
		if (!itab.backslash && !itab.cur_quote && (str[itab.i] == '$'))
			itab.i += go_to_var_end(str + itab.i) - 1;
		else if (!itab.backslash && !itab.cur_quote && (str[itab.i] == '('))
			itab.ret++;
		else if (!itab.backslash && !itab.cur_quote && (str[itab.i] == ')'))
			itab.ret--;
		if (!itab.ret)
			break ;
	}
	dest = ft_substr(str, 1, itab.i - 1);
	free(str);
	return (dest);
}
