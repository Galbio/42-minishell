/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 03:38:49 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/11 18:22:40 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*split_pipes(char *str)
{
	t_int_tab	itab;
	t_list		*commands;

	itab = init_int_tab();
	commands = NULL;
	while (str[++itab.i])
	{
		if ((str[itab.i] == '|') && !itab.backslash && !itab.cur_quote
				&& (str[itab.i + 1] != '|'))
		{
			itab.ptr1 = ft_substr(str, itab.ret, itab.i - itab.ret);
			itab.ret = itab.i + 1;
			ft_lstadd_back(&commands,
				ft_lstnew(ft_strtrim(itab.ptr1, " \n\t\r\b\v\f")));
			free(itab.ptr1);
		}
		check_special_char(str[itab.i], &itab.backslash, &itab.cur_quote);
	}
	itab.ptr1 = ft_substr(str, itab.ret, itab.i);
	ft_lstadd_back(&commands,
		ft_lstnew(ft_strtrim(itab.ptr1, " \n\t\r\b\v\f")));
	free(itab.ptr1);
	return (commands);
}

t_list	*init_pipes(char *str, t_list **envp, t_main_envp *imp)
{
	char	*temp;
	t_list	*head;
	t_list	*cur;

	head = split_pipes(str);
	cur = head;
	while (cur)
	{
		temp = cur->content;
		cur->content = create_command_argv(cur->content, envp, imp);
		free(temp);
		cur = cur->next;
	}
	return (head);
}
