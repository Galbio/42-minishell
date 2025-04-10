/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:57:20 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/08 22:25:19 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_var_to_dest(char *dest, char *str, t_int_tab *itab,
		t_list **cmd_outputs)
{
	char		*to_add;
	int			len;
	t_list		*temp;

	to_add = ((char *)(*cmd_outputs)->content);
	len = ft_strlen(to_add);
	ft_memcpy(dest + itab->res, to_add, len);
	temp = *cmd_outputs;
	*cmd_outputs = temp->next;
	free(temp->content);
	free(temp);
	itab->res += len;
	if (ft_strchr("{(", str[itab->i + 1]))
		itab->i += get_subcmd_size(str + itab->i + 1);
	else if (!ft_strchr("~%+=]}./\\:\0", str[itab->i + 1]))
		itab->i += go_to_var_end(str + itab->i) - 1;
}

static int	get_parsed_size(char *str, t_list **cmd_outputs, t_cmd_params *cmd)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		if (check_special_char(str, &itab))
			continue ;
		if ((str[itab.i] == '$') && (itab.cur_quote != '\'') && !itab.backslash)
			handle_var(str, &itab, cmd_outputs, cmd);
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

static void	fill_dest(char *dest, t_int_tab *itab, char *str,
			t_list **cmd_outputs)
{
	itab->backslash = itab->i && (str[itab->i - 1] == '\\') && !itab->backslash;
	if (check_special_char(str, itab))
		return ;
	if ((str[itab->i] == '$') && (itab->cur_quote != '\'') && !itab->backslash)
		add_var_to_dest(dest, str, itab, cmd_outputs);
	else
	{
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
}

char	*parse_quotes(char *str, t_cmd_params *cmd)
{
	char		*dest;
	t_list		*cmd_outputs;
	t_int_tab	itab;

	itab = init_int_tab();
	cmd_outputs = NULL;
	itab.ret = get_parsed_size(str, &cmd_outputs, cmd);
	dest = malloc(sizeof(char) * (itab.ret + 1));
	if (!dest)
		return (NULL);
	while (str[++itab.i])
		fill_dest(dest, &itab, str, &cmd_outputs);
	dest[itab.ret] = 0;
	free(str);
	return (dest);
}

void	add_to_argv(t_list **dest, char *str, t_int_tab *itab,
		t_cmd_params *cmd)
{
	if (!str[itab->ret])
		return ;
	cmd->extra = dest;
	add_splitted_to_add(parse_quotes(
			ft_substr(str, itab->ret, itab->i - itab->ret), cmd), dest);
	while (str[itab->i] && ft_strchr(" \n\t", str[itab->i]))
		itab->i++;
	itab->ret = itab->i--;
}
