/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:21:06 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/12 15:51:53 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	list_aliases(t_list *cur, int len)
{
	char	*val;
	int		i;

	while (cur && len--)
	{
		i = 0;
		val = (char *)cur->content;
		while (val[i] && (val[i] != '='))
			i++;
		printf("alias %.*s'", i + 1, val);
		while (val[++i])
		{
			if (val[i] == '\'')
				printf("'\\'");
			printf("%c", *(val + i));
		}
		printf("'\n");
		cur = cur->next;
	}
}

static void	display_error(char *name, int code)
{
	int		i;

	if (code == 0)
	{
		translate(2, "command.alias.notfound",
			program_arg("alias", new_arg(name, NULL)), 1);
		return ;
	}
	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	name[i] = '\0';
	translate(2, "command.alias.invalid",
		program_arg("alias", new_arg(name, NULL)), 1);
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
	ft_lstadd_front(&imp->aliases, ft_lstnew(ft_strdup(name)));
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
	{
		list_aliases(cmd->imp->aliases, -1);
		return (0);
	}
	i = 0;
	res = 0;
	while (cmd->argv[++i])
	{
		if (ft_strchr(cmd->argv[i], '='))
			res += add_alias(cmd->argv[i], cmd->imp);
		else
			res += print_single_alias(cmd->argv[i], cmd->imp);
	}
	return (res && 1);
}
