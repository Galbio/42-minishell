/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredocs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:54:43 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/04 13:35:07 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_parsed_size(char *str, t_main_envp *imp)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		if (check_special_char(str, &itab))
			continue ;
		if (!itab.backslash && !itab.cur_quote
			&& ft_strchr("<> \t", str[itab.i]))
			break ;
		else
		{
			if (itab.cur_quote && ft_strchr(" \n\t\\", str[itab.i]))
				itab.res++;
			itab.res++;
			if (!itab.cur_quote && itab.backslash
				&& (str[itab.i] == '\\') && (str[itab.i + 1] == '\\'))
				continue ;
		}
	}
	ft_lstadd_back(&imp->heredocs_infos,
		ft_lstnew((void *)imp->actual_pos + itab.i - 1));
	return (itab.res);
}

static char	fill_dest(char *dest, t_int_tab *itab, char *str)
{
	itab->backslash = itab->i && (str[itab->i - 1] == '\\') && !itab->backslash;
	if (check_special_char(str, itab))
		return (0);
	if (!itab->backslash && !itab->cur_quote
		&& ft_strchr("<> \t", str[itab->i]))
		return (1);
	if (itab->cur_quote && ft_strchr(" \n\t\\", str[itab->i]))
		dest[itab->res++] = '\\';
	dest[itab->res++] = str[itab->i];
	if (!itab->cur_quote && itab->backslash
		&& (str[itab->i] == '\\') && (str[itab->i + 1] == '\\'))
		return (0);
}

char	*parse_heredoc_value(char *str, t_main_envp *imp)
{
	char		*dest;
	t_int_tab	itab;

	itab = init_int_tab();
	itab.ret = get_parsed_size(str, imp);
	dest = malloc(sizeof(char) * (itab.ret + 1));
	if (!dest)
		return (NULL);
	while (str[++itab.i])
		if (fill_dest(dest, &itab, str))
			break ;
	dest[itab.ret] = 0;
	return (dest);
}
