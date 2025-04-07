/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:16:33 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/08 01:15:23 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_if_is_exist(char *str, t_list **envp, int equal_pos)
{
	char	*value;
	t_list	*cur;

	cur = *envp;
	while (cur)
	{
		value = (char *)cur->content;
		if (!ft_strncmp(str, value + (value[0] == '\\'), equal_pos))
		{
			if (value[0] != '\\')
				cur->content = ft_strdup(str);
			else
				cur->content = ft_strjoin("\\", str);
			free(value);
			return ;
		}
		cur = cur->next;
	}
	ft_lstadd_back(envp, ft_lstnew(ft_strjoin("\\", str)));
}

static void	add_local(char *str, t_int_tab *itab, t_cmd_params *cmd, int i)
{
	char	*value;
	int		equal_pos;

	equal_pos = i;
	while (str[i] && !ft_strchr(" \n\t", str[i]))
		i++;
	value = parse_quotes(ft_substr(str, 0, i), cmd);
	update_if_is_exist(value, cmd->envp, equal_pos);
	free(value);
	while (str[i] && ft_strchr(" \n\t", str[i]))
		i++;
	itab->ret = i;
	itab->i = i - 1;
}

void	handle_local_appending(char *str, t_int_tab *itab, t_cmd_params *cmd)
{
	int		i;

	if (ft_isdigit(str[0]))
		return ;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
		if (!ft_isalnum(str[i]) && (str[i] != '_'))
			return ;
	}
	add_local(str, itab, cmd, i);
}
