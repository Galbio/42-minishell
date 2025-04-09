/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:21:06 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/09 03:05:43 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	list_aliases(t_list *cur, int len)
{
	char	*val;
	int		i;

	while (cur && len--)
	{
		val = (char *)cur->content;
		write(1, "alias ", 6);
		i = 0;
		while (val[i] && (val[i] != '='))
			i++;
		write(1, val, i + 1);
		write(1, "'", 1);
		while (val[++i])
		{
			if (val[i] == '\'')
				write(1, "'\\'", 3);
			write(1, val + i, 1);
		}
		write(1, "'\n", 2);
		cur = cur->next;
	}
	return (0);
}

static void	display_error(char *name, int code)
{
	int		i;

	if (code == 0)
	{
		write(2, "minishell: alias: ", 18);
		write(2, name, ft_strlen(name));
		write(2, ": not found\n", 12);
		return ;
	}
	write(2, "minishell: alias: `", 19);
	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	write(2, name, i);
	write(2, "': invalid alias name\n", 22);
}

static int	add_alias(char *name, t_main_envp *imp)
{
	int		i;

	i = -1;
	if (name[0] == '=')
	{
		display_error(name, 0);
		return (1);
	}
	while (name[++i] && (name[i] != '='))
	{
		if (ft_strchr("$&()\"'/\\ \t`", name[i]))
		{
			display_error(name, 1);
			return (1);
		}
	}
	ft_lstadd_back(&imp->aliases, ft_lstnew(ft_strdup(name)));
	return (0);
}

static int	print_single_alias(char *name, t_main_envp *imp)
{
	t_list	*cur;
	char	*alias;
	int		len;

	len = ft_strlen(name);
	cur = imp->aliases;
	while (cur)
	{
		alias = (char *)cur->content;
		if (!ft_strncmp(name, alias, len) && (alias[len] == '='))
		{
			list_aliases(cur, 1);
			return (0);
		}
		cur = cur->next;
	}
	display_error(name, 0);
	return (1);
}

int	ms_alias(t_cmd_params *cmd)
{
	int		i;
	int		res;

	if (!cmd->argv[1] || (cmd->argv[1][0] == '#'))
		return (list_aliases(cmd->imp->aliases, -1));
	i = 0;
	res = 0;
	while (cmd->argv[++i])
	{
		if (ft_strchr(cmd->argv[i], '='))
			res += add_alias(cmd->argv[i], cmd->imp);
		else
			res += print_single_alias(cmd->argv[i], cmd->imp);
	}
	return (0);
}
