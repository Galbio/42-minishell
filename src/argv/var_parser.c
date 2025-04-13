/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 03:46:01 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/13 20:15:26 by gakarbou         ###   ########.fr       */
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
			return (parse_var_return(ft_strdup(value + len + 1)));
		cur = cur->next;
	}
	return (NULL);
}

static char	*handle_braces(char *str, t_cmd_params *cmd, char *src)
{
	if (ft_strchr("0123456789!@$%^&*()[]{},./?\\ \t\n", str[0]))
	{
		write(2, "minishell: ", 11);
		ft_putstr_fd(src, 2);
		write(2, ": bad substitution\n", 19);
		set_exit_status(257);
		return (NULL);
	}
	return (handle_brace_option(str, cmd, src));
}

static char	*get_var_output(char *str, t_int_tab *itab, t_cmd_params *cmd)
{
	if (ft_strchr("{(", str[itab->i + 1]))
	{
		itab->ptr2 = str;
		if (str[itab->i + 1] == '(')
			return (handle_commands(itab, cmd));
		return (handle_braces(itab->ptr1, cmd, str));
	}
	else
	{
		if (itab->ptr1[0] == '?')
			return (ft_itoa(get_exit_status()));
		else if (itab->ptr1[0] == '#')
			return (ft_itoa(0));
		return (get_var_value(itab->ptr1, *(cmd->envp)));
	}
	return (NULL);
}

static char	*handle_var_replacing(char *str, t_int_tab *itab, t_cmd_params *cmd)
{
	int		is_cmd;
	char	*dest;
	void	*temp;

	if (ft_strchr(" \n\t~@^%=+]}'\":,./", str[itab->i + 1]))
		return (str);
	is_cmd = 0;
	if (ft_strchr("({", str[itab->i + 1]))
	{
		is_cmd = 2;
		itab->ptr1 = get_subcmd(str + itab->i + 1);
	}
	else
		itab->ptr1 = get_var_name(str + itab->i + 1);
	temp = get_var_output(str, itab, cmd);
	if (!temp)
		temp = ft_strdup("");
	dest = ft_strreplace_part(str, itab->i,
			ft_strlen(itab->ptr1) + is_cmd + 1, temp);
	free(itab->ptr1);
	free(str);
	free(temp);
	return (dest);
}

char	*replace_var(char *str, t_cmd_params *cmd)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		if (check_special_char(str, &itab))
			continue ;
		if (!itab.backslash && (itab.cur_quote != '\'') && (str[itab.i] == '$'))
			str = handle_var_replacing(str, &itab, cmd);
	}
	return (str);
}
