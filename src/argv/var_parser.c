/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 03:46:01 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/07 23:55:03 by gakarbou         ###   ########.fr       */
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
		value += (value[0] == '\\');
		if ((value[len] == '=') && !ft_strncmp(name, value, len))
			return (parse_var_return(ft_strdup(value + len + 1), quote));
		cur = cur->next;
	}
	return (NULL);
}

static char	*handle_braces(char *str, t_cmd_params *cmd, char quote)
{
	char	*dest;
	char	*temp;

	if (*str == '#')
	{
		if (str[1] == '#')
			return (ft_itoa(0));
		dest = handle_braces(str + 1, cmd, quote);
		temp = dest;
		dest = ft_itoa(ft_strlen(dest));
		free(temp);
		return (dest);
	}
	if (*str == '?')
		return (ft_itoa((int)cmd->imp->exit_status));
	dest = get_var_value(str, *(cmd->envp), quote);
	if (!dest)
		dest = ft_strdup("");
	return (dest);
}

static char	*get_var_output(char *str, t_int_tab *itab, t_list **cmd_outputs,
		t_cmd_params *cmd)
{
	if (ft_strchr("{(", str[itab->i + 1]))
	{
		itab->ptr1 = get_subcmd(str + itab->i + 1);
		itab->ptr2 = str;
		if (str[itab->i + 1] == '(')
			return (handle_commands(itab, cmd, cmd_outputs));
		return (handle_braces(itab->ptr1, cmd, itab->cur_quote));
	}
	else
	{
		itab->ptr1 = get_var_name(str + itab->i + 1);
		if (itab->ptr1[0] == '?')
			return (ft_itoa((int)cmd->imp->exit_status));
		else if (itab->ptr1[0] == '#')
			return (ft_itoa(0));
		return (get_var_value(itab->ptr1, *(cmd->envp), itab->cur_quote));
	}
	return (NULL);
}

void	handle_var(char *str, t_int_tab *itab, t_list **cmd_outputs,
		t_cmd_params *cmd)
{
	char	*output;

	if (ft_strchr("~%+=]}./\\:\0", str[itab->i + 1]))
	{
		ft_lstadd_back(cmd_outputs, ft_lstnew(ft_strdup("$")));
		itab->res++;
		return ;
	}
	output = get_var_output(str, itab, cmd_outputs, cmd);
	if (!output)
		output = ft_strdup("");
	ft_lstadd_back(cmd_outputs, ft_lstnew(output));
	itab->res += ft_strlen(output);
	itab->i += ft_strlen(itab->ptr1)
		+ (2 * (ft_strchr("({", str[itab->i + 1]) != 0));
	free(itab->ptr1);
}
