/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:57:20 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/13 22:55:02 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_parsed_size(char *str)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		if (check_special_char(str, &itab))
			continue ;
		else
		{
			if (itab.cur_quote && ft_strchr(" \n\t\\", str[itab.i]))
				itab.res++;
			else if (ft_strchr("*[?", str[itab.i])
				&& (itab.cur_quote || itab.backslash))
				itab.res++;
			itab.res++;
			if (!itab.cur_quote && itab.backslash
				&& (str[itab.i] == '\\') && (str[itab.i + 1] == '\\'))
				continue ;
		}
	}
	return (itab.res);
}

static void	fill_dest(char *dest, t_int_tab *itab, char *str)
{
	itab->backslash = itab->i && (str[itab->i - 1] == '\\') && !itab->backslash;
	if (check_special_char(str, itab))
		return ;
	if (itab->cur_quote && ft_strchr(" \n\t\\", str[itab->i]))
		dest[itab->res++] = '\\';
	else if (ft_strchr("*[?", str[itab->i])
		&& (itab->cur_quote || itab->backslash))
		dest[itab->res++] = '\\';
	dest[itab->res++] = str[itab->i];
	if (!itab->cur_quote && itab->backslash
		&& (str[itab->i] == '\\') && (str[itab->i + 1] == '\\'))
		return ;
}

char	*parse_quotes(char *str, t_cmd_params *cmd)
{
	char		*dest;
	t_int_tab	itab;

	itab = init_int_tab();
	str = replace_var(str, cmd);
	if (!str[0])
	{
		free(str);
		return (NULL);
	}
	itab.ret = get_parsed_size(str);
	dest = malloc(sizeof(char) * (itab.ret + 1));
	if (!dest)
		return (NULL);
	while (str[++itab.i])
		fill_dest(dest, &itab, str);
	dest[itab.ret] = 0;
	free(str);
	return (dest);
}

void	add_to_argv(t_list **dest, char *str, t_int_tab *itab,
		t_cmd_params *cmd)
{
	char	*parsed;

	if (!str[itab->ret])
		return ;
	cmd->extra = dest;
	parsed = parse_quotes(ft_substr(str, itab->ret, itab->i - itab->ret), cmd);
	if (parsed)
		add_splitted_to_add(parsed, dest);
	while (str[itab->i] && ft_strchr(" \n\t", str[itab->i]))
		itab->i++;
	itab->ret = itab->i--;
}
