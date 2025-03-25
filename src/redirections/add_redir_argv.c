/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:20:19 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/25 14:28:31 by gakarbou         ###   ########.fr       */
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

static void	add_method(char *str, t_int_tab *itab, t_cmd_params *cmd)
{
	int		i;
	int		j;

	i = 0;
	if (itab->i && (str[itab->i - 1] == '&'))
		i = 1;
	else if (itab->i)
		while ((itab->i - i) && ft_isdigit(str[itab->i - i - 1]))
			i++;
	j = 0;
	while (ft_strchr("<>", str[itab->i + j]))
		j++;
	if ((j == 2) && (str[itab->i + 2] == '-')
		&& !ft_strncmp("<<", str + itab->i, 2))
		j++;
	ft_lstadd_back(&(cmd->redir), ft_lstnew(
			ft_substr(str + itab->i - i, 0, j + i)));
	itab->i += j;
}

void	add_redirection(char *str, t_int_tab *itab,
		t_cmd_params *cmd, t_list **dest)
{
	int		i;
	char	*to_add;

	if (itab->i && ((str[itab->i - 1] == '&') || ft_isdigit(str[itab->i - 1])))
		;
	else if (itab->i && !ft_strchr(" \t\n", str[itab->i - 1]))
	{
		add_to_argv(dest, str, itab, cmd);
		itab->i++;
	}
	i = 0;
	add_method(str, itab, cmd);
	while (ft_strchr(" \n\t", str[itab->i]))
		itab->i++;
	to_add = get_redirect_text(str + itab->i);
	itab->i += ft_strlen(to_add);
	ft_lstadd_back(&(cmd->redir), ft_lstnew(parse_quotes(to_add, cmd)));
	itab->ret = itab->i;
}
