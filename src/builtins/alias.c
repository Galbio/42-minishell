/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:21:06 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/13 02:38:37 by gakarbou         ###   ########.fr       */
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

static void	display_invalid_alias(char *name)
{
	int		i;

	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	write(2, "minishell: alias: `", 19);
	write(2, name, i);
	write(2, "': invalid alias name\n", 22);
}

static int	add_alias(char *name, t_main_envp *imp)
{
	int		i;

	i = -1;
	if (name[0] == '=')
		return (display_error("minishell: alias: ", name, ":not found\n", 1));
	while (name[++i] && (name[i] != '='))
	{
		if (ft_strchr("$&()\"'/\\ \t`", name[i]))
			return (display_error("minishell: alias: ",
					name, ":not found\n", 1));
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
	display_invalid_alias(name);
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
