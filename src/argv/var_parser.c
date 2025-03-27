/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 03:46:01 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 16:28:33 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(char *name, t_list *cur, char quote)
{
	int		len;
	char	*value;

	len = ft_strlen(name);
	while (cur)
	{
		value = (char *)cur->content;
		if ((value[len] == '=') && !ft_strncmp(name, value, len))
			return (parse_var_return(ft_strdup(value + len + 1), quote));
		cur = cur->next;
	}
	return (NULL);
}

static char	*get_cmd(char *str)
{
	t_int_tab	itab;

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
			return (ft_substr(str, 1, itab.i - 1));
	}
	return (ft_substr(str, 1, itab.i - 1));
}

static void	add_cmd_output(char *str, t_int_tab *itab,
		char *output, t_list **cmd_outputs)
{
	if (!output && (str[itab->i + 1] != '{'))
	{
		output = ft_strdup("$");
		free(itab->ptr1);
		itab->res++;
		ft_lstadd_back(cmd_outputs, ft_lstnew(output));
		return ;
	}
	else if (!output)
		output = ft_strdup("");
	ft_lstadd_back(cmd_outputs, ft_lstnew(output));
	itab->res += ft_strlen(output);
	itab->i += ft_strlen(itab->ptr1)
		+ (2 * (ft_strchr("({", str[itab->i + 1]) != 0));
	free(itab->ptr1);
}

void	handle_var(char *str, t_int_tab *itab, t_list **cmd_outputs,
		t_cmd_params *cmd)
{
	char	*output;

	if (str[itab->i + 1] == '(')
	{
		itab->ptr1 = get_cmd(str + itab->i + 1);
		itab->ptr2 = str;
		output = handle_commands(itab, cmd, cmd_outputs);
	}
	else
	{
		itab->ptr1 = get_var_name(str + itab->i + 1);
		if (itab->ptr1[0] == '?')
			output = ft_itoa((int)cmd->imp->exit_status);
		else
			output = get_var_value(itab->ptr1, *(cmd->envp), itab->cur_quote);
	}
	add_cmd_output(str, itab, output, cmd_outputs);
}
