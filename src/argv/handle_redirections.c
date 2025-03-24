/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:20:19 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/25 00:03:23 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_redirect_text(char *str)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(str, &itab);
		if (!itab.backslash && !itab.cur_quote
			&& ft_strchr(" \n\t", str[itab.i]))
			return (ft_substr(str, 0, itab.i));
		if (!itab.backslash && !itab.cur_quote && (str[itab.i] == '$'))
			itab.i += go_to_var_end(str + itab.i) - 1;
	}
	return (ft_substr(str, 0, itab.i));
}

void	add_redirection(char *str, t_int_tab *itab,
		t_cmd_params *cmd, t_list **dest)
{
	int		i;
	char	*to_add;

	i = 0;
	if (itab->i && !ft_strchr(" \t\n", str[itab->i - 1]))
	{
		add_to_argv(dest, str, itab, cmd);
		itab->i++;
	}
	while (str[itab->i + i] == '<')
		i++;
	ft_lstadd_back(&(cmd->redir), ft_lstnew(ft_substr(str + itab->i, 0, i)));
	itab->i += i;
	while (ft_strchr(" \n\t", str[itab->i]))
		itab->i++;
	to_add = get_redirect_text(str + itab->i);
	itab->i += ft_strlen(to_add);
	ft_lstadd_back(&(cmd->redir), ft_lstnew(parse_quotes(to_add, cmd)));
	itab->ret = itab->i;
}
