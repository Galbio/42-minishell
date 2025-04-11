/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redir_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:20:19 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/10 17:44:49 by gakarbou         ###   ########.fr       */
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
		if (!itab.backslash && (itab.cur_quote != '\'') && (str[itab.i] == '$')
			&& ft_strchr("({", str[itab.i + 1]))
			itab.i += get_subcmd_size(str + itab.i);
	}
	return (ft_substr(str, 0, itab.i));
}

static char	*get_method(char *str, t_int_tab *itab)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	if (itab->i && (str[itab->i - 1] == '&'))
		i = 1;
	else if (itab->i)
		while ((itab->i - i) && ft_isdigit(str[itab->i - i - 1]))
			i++;
	j = 0;
	while (str[itab->i + j] && ft_strchr("<>", str[itab->i + j]))
		j++;
	if ((j == 2) && (str[itab->i + 2] == '-')
		&& !ft_strncmp("<<", str + itab->i, 2))
		j++;
	dest = ft_substr(str + itab->i - i, 0, j + i);
	itab->i += j;
	return (dest);
}

static char	**parse_redirect_value(char *to_add, t_int_tab *itab,
		t_cmd_params *cmd)
{
	char	**dest;

	itab->i += ft_strlen(to_add);
	if (to_add[0])
	{
		dest = fill_return_argv(fill_argv(to_add, cmd));
	}
	else
	{
		to_add = NULL;
		dest = NULL;
	}
	itab->ret = itab->i;
	return (dest);
}

void	add_redirection(char *str, t_int_tab *itab,
		t_cmd_params *cmd, t_list **dest)
{
	t_redirection	*to_add;

	to_add = malloc(sizeof(t_redirection));
	if (!to_add)
		return ;
	if (itab->i && ((str[itab->i - 1] == '&') || ft_isdigit(str[itab->i - 1])))
		;
	else if (itab->i && !ft_strchr(" \t\n", str[itab->i - 1]))
	{
		add_to_argv(dest, str, itab, cmd);
		itab->i++;
	}
	to_add->method = get_method(str, itab);
	to_add->is_fd = 0;
	if ((str[itab->i] == '&') && is_only_nb(str + itab->i + 1))
	{
		to_add->is_fd++;
		itab->i++;
	}
	while (str[itab->i] && ft_strchr(" \n\t", str[itab->i]))
		itab->i++;
	to_add->og_str = get_redirect_text(str + itab->i);
	to_add->values = parse_redirect_value(to_add->og_str, itab, cmd);
	ft_lstadd_back(&(cmd->redir), ft_lstnew(to_add));
}
