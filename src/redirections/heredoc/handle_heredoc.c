/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:06:57 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/14 00:41:09 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_heredocs(char *str, t_int_tab *itab,
		t_list **heredocs, t_main_envp *imp)
{
	char	ignore_tab;
	char	*value;
	char	*content;

	ignore_tab = 0;
	if (advance_itab(str, itab, &ignore_tab, str[itab->i]))
		return ;
	ft_lstadd_back(&imp->heredocs_infos,
		ft_lstnew((void *)imp->actual_pos + itab->i));
	imp->actual_pos += itab->i;
	value = parse_heredoc_value(str + itab->i, imp);
	imp->actual_pos -= itab->i;
	content = wait_value(heredocs, value, ignore_tab, imp->cmd_count);
	ft_lstadd_back(&imp->heredocs_infos,
		ft_lstnew(parse_heredoc_quote(content)));
	free(value);
	free(content);
}

static void	add_heredocs_subcmd(char *str, t_list **heredocs, t_main_envp *imp)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(str, &itab);
		if (!itab.cur_quote && (str[itab.i] == '\n'))
			break ;
		if (!itab.backslash && (itab.cur_quote != '\'') && (str[itab.i] == '$')
			&& (str[itab.i + 1] == '('))
		{
			imp->actual_pos += itab.i + 2;
			add_heredocs_subcmd(get_subcmd(str + itab.i + 1), heredocs, imp);
			imp->actual_pos -= itab.i + 2;
			itab.i += go_to_var_end(str + itab.i) - 1;
		}
		else if (!itab.backslash && !itab.cur_quote
			&& ft_strchr("<>", str[itab.i]))
			check_heredocs(str, &itab, heredocs, imp);
		if (get_exit_status() >= 256)
			break ;
	}
	free(str);
}

static char	*replace_heredocs(char *str, t_list *infos)
{
	long	i;
	long	end;
	long	len_diff;
	void	*temp;
	void	*head;

	head = infos;
	len_diff = 0;
	while (infos)
	{
		i = (long)infos->content + len_diff;
		end = (long)infos->next->content + len_diff;
		temp = str;
		str = ft_strreplace_part(str, i, end - i + 1,
				infos->next->next->content);
		free(temp);
		len_diff += ft_strlen(infos->next->next->content) - (end - i + 1);
		infos = infos->next->next->next;
	}
	free_heredocs(head);
	return (str);
}

static int	check_line_end(char *str, t_list **heredocs, t_main_envp *imp,
		t_int_tab	*itab)
{
	itab->backslash = itab->i && (str[itab->i - 1] == '\\') && !itab->backslash;
	check_special_char(str, itab);
	if (!itab->cur_quote && (str[itab->i] == '\n'))
		return (1);
	if (!itab->backslash && (itab->cur_quote != '\'') && (str[itab->i] == '$')
		&& (str[itab->i + 1] == '('))
	{
		imp->actual_pos += itab->i + 2;
		add_heredocs_subcmd(get_subcmd(str + itab->i + 1), heredocs, imp);
		imp->actual_pos -= itab->i + 2;
		itab->i += go_to_var_end(str + itab->i) - 1;
	}
	else if (!itab->backslash && !itab->cur_quote
		&& ft_strchr("<>", str[itab->i]))
		check_heredocs(str, itab, heredocs, imp);
	if (get_exit_status() >= 256)
		return (1);
	return (0);
}

char	*identify_heredoc(char *str, t_list **heredocs, t_main_envp *imp)
{
	t_int_tab	itab;
	t_list		*head;

	itab = init_int_tab();
	head = *heredocs;
	itab.ptr1 = ft_strdup(head->content);
	while (str[++itab.i])
		if (check_line_end(str, heredocs, imp, &itab))
			break ;
	add_heredoc_history(head, heredocs, imp);
	return (replace_heredocs(itab.ptr1, imp->heredocs_infos));
}
