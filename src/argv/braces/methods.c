/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:36:16 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/12 15:52:26 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*brace_if_not_defined(char *src, char *default_str, t_cmd_params *cmd)
{
	char	*name;
	char	*value;

	name = get_var_name(src);
	if (name[0] == '?')
		return (ft_itoa(get_exit_status()));
	value = get_var_value(name, *(cmd->envp));
	free(name);
	if (!value)
		return (ft_strdup(default_str + 1));
	return (value);
}

char	*brace_assign_if_not_defined(char *src, char *default_str,
		t_cmd_params *cmd)
{
	char	*temp;
	char	*name;
	char	*value;

	name = get_var_name(src);
	if (name[0] == '?')
		return (ft_itoa(get_exit_status()));
	value = get_var_value(name, *(cmd->envp));
	if (!value)
	{
		temp = ft_strjoin("\\", name);
		free(name);
		name = ft_strjoin(temp, "=");
		free(temp);
		ft_lstadd_back(cmd->envp, ft_lstnew(ft_strjoin(name, default_str + 1)));
		free(name);
		return (ft_strdup(default_str + 1));
	}
	free(name);
	return (value);
}

char	*brace_if_defined(char *src, char *default_str, t_cmd_params *cmd)
{
	char	*name;
	char	*value;

	name = get_var_name(src);
	if (name[0] == '?')
		return (ft_itoa(get_exit_status()));
	value = get_var_value(name, *(cmd->envp));
	free(name);
	if (value)
	{
		free(value);
		name = ft_strdup(default_str + 1);
		return (name);
	}
	return (ft_strdup(""));
}

char	*brace_error_if_not_defined(char *src, char *default_str,
		t_cmd_params *cmd)
{
	char	*name;
	char	*value;

	name = get_var_name(src);
	if (name[0] == '?')
		return (ft_itoa(get_exit_status()));
	value = get_var_value(name, *(cmd->envp));
	if (!value)
	{
		translate(2, "brace.notdef",
			program_arg(name, new_arg(default_str + 1, NULL)), 1);
		set_exit_status(257);
		free(name);
		return (ft_strdup(""));
	}
	free(name);
	return (value);
}
