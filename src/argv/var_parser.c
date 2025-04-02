/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 03:46:01 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 09:13:48 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_sub_cmd(t_int_tab *itab, t_cmd_params *cmd,
		int pipes[2], t_list **outputs)
{
	int			res;
	t_list		**envp;
	t_main_envp	*imp;

	ft_lstclear(outputs, free);
	ft_lstclear(cmd->extra, free);
	cmd->extra = NULL;
	free(itab->ptr2);
	imp = cmd->imp;
	envp = cmd->envp;
	close(pipes[0]);
	free_cmd(cmd, 1);
	free(cmd);
	imp->output_fd = pipes[1];
	imp->is_bquoted++;
	execute_line(itab->ptr1, envp, imp);
	res = imp->exit_status;
	free_envp(envp, imp);
	exit(res);
}

static char	*handle_commands(t_int_tab *itab, t_cmd_params *cmd,
		t_list **outputs)
{
	pid_t	pid;
	int		pipes[2];
	int		stat;
	char	*dest;

	if (pipe(pipes) < 0)
		return (NULL);
	pid = fork();
	if (!pid)
		execute_sub_cmd(itab, cmd, pipes, outputs);
	close(pipes[1]);
	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		cmd->imp->exit_status = WEXITSTATUS(stat);
	dest = ft_get_contents(pipes[0]);
	close(pipes[0]);
	return (parse_var_return(dest, itab->cur_quote));
}

char	*get_var_value(char *name, t_list *cur, char quote)
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
	return (NULL);
}

static char	*get_cmd(char *str)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(str, &itab);
		if (!itab.backslash && !itab.cur_quote && (str[itab.i] == '$'))
			itab.i += go_to_var_end(str + itab.i) - 1;
		else if (!itab.backslash && !itab.cur_quote && (str[itab.i] == '('))
			itab.ret++;
		else if (!itab.backslash && !itab.cur_quote && (str[itab.i] == ')'))
			itab.ret--;
		if (!itab.ret)
			return (ft_substr(str, 1, itab.i - 1));
	}
	return (ft_substr(str, 1, itab.i - 1));
}

void	handle_var(char *str, t_int_tab *itab, t_list **cmd_outputs,
		t_cmd_params *cmd)
{
	char	*output;

	if (str[itab->i + 1] == '(')
	{
		itab->ptr1 = get_cmd(str + itab->i + 1);
		itab->ptr2 = str;
		output = handle_commands(itab, cmd, cmd_outputs);
	}
	else
	{
		itab->ptr1 = get_var_name(str + itab->i + 1);
		if (itab->ptr1[0] == '?')
			output = ft_itoa((int)cmd->imp->exit_status);
		else
			output = get_var_value(itab->ptr1, *(cmd->envp), itab->cur_quote);
	}
	if (!output)
		output = ft_strdup("");
	ft_lstadd_back(cmd_outputs, ft_lstnew(output));
	itab->res += ft_strlen(output);
	itab->i += ft_strlen(itab->ptr1) + (2 * (str[itab->i +1] == '('));
	free(itab->ptr1);
}
