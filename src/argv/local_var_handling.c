/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:16:33 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/09 18:13:10 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_to_envp(char *str, t_list **envp, int equal_pos)
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
			free(str);
			return ;
		}
		cur = cur->next;
	}
	ft_lstadd_back(envp, ft_lstnew(ft_strjoin("\\", str)));
	free(str);
}

static void	add_local(char *str, t_int_tab *itab,
		t_cmd_params *cmd, int equal_pos)
{
	char	*value;
	char	*to_add;
	int		i;

	value = parse_quotes(ft_substr(str, equal_pos + 1, itab->i), cmd);
	i = 0;
	to_add = make_splitted_str(&value, &i, 1);
	free(value);
	i = equal_pos;
	value = ft_substr(str, 0, equal_pos + 1);
	add_to_envp(ft_strjoin(value, to_add), cmd->envp, equal_pos);
	free(value);
	free(to_add);
	while (str[itab->i] && ft_strchr(" \n\t", str[itab->i]))
		itab->i++;
	itab->ret = itab->i--;
}

void	handle_local_appending(char *str, t_int_tab *itab, t_cmd_params *cmd)
{
	int		i;
	int		equal_pos;

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
	itab->i = i;
	equal_pos = itab->i;
	while (str[++itab->i])
	{
		itab->backslash = itab->i && (str[itab->i - 1] == '\\')
			&& !itab->backslash;
		check_special_char(str, itab);
		if (!itab->backslash && !itab->cur_quote
			&& ft_strchr(" \n\t", str[itab->i]))
			break ;
	}
	add_local(str, itab, cmd, equal_pos);
}
