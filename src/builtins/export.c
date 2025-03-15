/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:04:41 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/13 23:08:16 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_error(char *name)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	add_envp(char *name, t_list **envp)
{
	char	*var_name;
	int		i;

	i = -1;
	if (!name[0] || (name[0] == '=') || ft_isdigit(name[0]))
	{
		display_error(name);
		return (1);
	}
	while (name[++i])
	{
		if (name[i] == '=')
			break ;
		if ((name[i] != '_') && !ft_isalnum(name[i]))
		{
			display_error(name);
			return (1);
		}
	}
	if (name[i] != '=')
		return (1);
	var_name = ft_substr(name, 0, i);
	unset_var(var_name, envp, NULL);
	ft_lstadd_back(envp, ft_lstnew(name));
	return (0);
}

int	ms_export(t_cmd_params *cmd)
{
	int		i;
	int		res;

	if (!cmd->argv[1])
	{
		export_vars(*(cmd->envp));
		return (0);
	}
	res = 0;
	i = 0;
	while (cmd->argv[++i])
		res += add_envp(cmd->argv[i], cmd->envp);
	return (res && 1);
}
