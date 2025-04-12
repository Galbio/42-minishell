/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 03:46:01 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/12 15:16:39 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(char *name, t_list *cur)
{
	int		len;
	char	*value;

	len = ft_strlen(name);
	while (cur)
	{
		value = (char *)cur->content;
		if (value[0] == '\\')
			value++;
		if (!ft_strncmp(name, value, len) && (value[len] == '='))
			return (parse_var_return(ft_strdup(value + len + 1), 1));
		cur = cur->next;
	}
	return (NULL);
}

static char	*handle_braces(char *str, t_cmd_params *cmd, char *src)
{
	if (ft_strchr("0123456789!@$%^&*()[]{},./?\\ \t\n", str[0]))
	{
		translate(2, "braces.badsub", program_arg(src, NULL), 1);
		set_exit_status(257);
		return (NULL);
	}
	return (handle_brace_option(str, cmd, src));
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
		return (handle_braces(itab->ptr1, cmd, str));
	}
	else
	{
		itab->ptr1 = get_var_name(str + itab->i + 1);
		if (itab->ptr1[0] == '?')
			return (ft_itoa(get_exit_status()));
		else if (itab->ptr1[0] == '#')
			return (ft_itoa(0));
		return (get_var_value(itab->ptr1, *(cmd->envp)));
	}
	return (NULL);
}

void	handle_var(char *str, t_int_tab *itab, t_list **cmd_outputs,
		t_cmd_params *cmd)
{
	char	*output;

	if (ft_strchr("~%+=]}./\\:\0", str[itab->i + 1]))
	{
		output = ft_strdup("$");
		itab->ptr1 = ft_strdup("");
	}
	else
		output = get_var_output(str, itab, cmd_outputs, cmd);
	if (!output)
		output = ft_strdup("");
	ft_lstadd_back(cmd_outputs, ft_lstnew(output));
	itab->res += ft_strlen(output);
	itab->i += ft_strlen(itab->ptr1)
		+ (2 * (ft_strchr("({", str[itab->i + 1]) != 0));
	free(itab->ptr1);
}
