/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:43:48 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/11 19:35:54 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*(*get_function(char *method))(char *src,
		char *default_str, t_cmd_params *cmd)
{
	if (method[1] == '-')
		return (brace_if_not_defined);
	if (method[1] == '=')
		return (brace_assign_if_not_defined);
	if (method[1] == '?')
		return (brace_error_if_not_defined);
	if (method[1] == '+')
		return (brace_if_defined);
	return (NULL);
}

char	*handle_brace_option(char *str, t_cmd_params *cmd, char *src)
{
	char	*dest;
	char	*temp;
	char	*(*function)(char *src, char *default_str, t_cmd_params *cmd);

	if (str[0] == '#')
	{
		if (str[1] == '#')
			return (ft_itoa(0));
		dest = handle_brace_option(str + 1, cmd, src);
		temp = dest;
		dest = ft_itoa(ft_strlen(dest));
		free(temp);
		return (dest);
	}
	temp = ft_strchr(str, ':');
	function = NULL;
	if (temp)
		function = get_function(temp);
	if (function)
		return (function(str, temp + 1, cmd));
	if (*str == '?')
		return (ft_itoa(get_exit_status()));
	return (get_var_value(str, *(cmd->envp)));
}
