/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 03:46:01 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/24 14:40:10 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_commands(char *name, t_cmd_params cmd, char quote)
{
	int		pipes[2];
	int		old_redir;
	char	*dest;

	if (pipe(pipes) < 0)
		return (NULL);
	old_redir = cmd.imp->output_fd;
	cmd.imp->output_fd = pipes[1];
	execute_line(split_semicolon(name), cmd.envp, cmd.imp);
	cmd.imp->output_fd = old_redir;
	close(pipes[1]);
	dest = ft_get_contents(pipes[0]);
	close(pipes[0]);
	return (parse_var_return(dest, quote));
}

static char	*get_var_value(char *name, t_list *cur, char quote)
{
	int		len;
	char	*value;

	len = ft_strlen(name);
	while (cur)
	{
		value = (char *)cur->content;
		if ((value[len] == '=') && !ft_strncmp(name, value, len))
			return (parse_var_return(ft_strdup(value + len + 1), quote));
		cur = cur->next;
	}
	return (ft_strdup(""));
}

void	handle_var(char *str, t_int_tab *itab, t_list **cmd_outputs,
		t_cmd_params cmd)
{
	char	*output;

	itab->ptr1 = get_var_name(str + itab->i + 1);
	if (itab->ptr1[0] == '?')
		output = ft_itoa((int)cmd.imp->exit_status);
	else if (itab->ptr1[0] == '(')
		output = handle_commands(itab->ptr1, cmd, itab->cur_quote);
	else
		output = get_var_value(itab->ptr1, *(cmd.envp), itab->cur_quote);
	ft_lstadd_back(cmd_outputs, ft_lstnew(output));
	itab->res += ft_strlen(output);
	itab->i += ft_strlen(itab->ptr1);
	free(itab->ptr1);
}
