/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:04:41 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/08 01:13:56 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_error(char *name)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	check_invalid_name(char *name, int *i)
{
	*i = -1;
	if (!name[0] || (name[0] == '=') || ft_isdigit(name[0]))
	{
		display_error(name);
		return (1);
	}
	while (name[++(*i)])
	{
		if (name[*i] == '=')
			break ;
		if ((name[*i] != '_') && !ft_isalnum(name[*i]))
		{
			display_error(name);
			return (1);
		}
	}
	return (0);
}

static int	add_envp(char *name, t_list **envp)
{
	char	*value;
	t_list	*cur;
	int		i;

	if (check_invalid_name(name, &i))
		return (1);
	cur = *envp;
	while (cur)
	{
		value = (char *)cur->content;
		if (!ft_strncmp(value + (value[0] == '\\'), name, i))
		{
			if (value[0] == '\\')
				cur->content = ft_strdup(value + 1);
			else
				cur->content = ft_strdup(name);
			free(value);
			return (0);
		}
		cur = cur->next;
	}
	ft_lstadd_back(envp, ft_lstnew(ft_strdup(name)));
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
