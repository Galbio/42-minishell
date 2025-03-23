/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:04:40 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/23 19:44:42 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_single_command(t_cmd_params cmd)
{
	pid_t		pid;
	int			temp;
	int			res;

	res = cmd.imp->exit_status;
	temp = check_builtins(cmd.argv[0]);
	dup2(cmd.imp->output_fd, 1);
	if (temp)
		return (handle_builtins(temp, &cmd));
	else if (!cmd.argv[0][0])
		return (res);
	pid = fork();
	if (pid < 0)
		return (1);
	if (!pid)
		execute_bin(cmd.argv, cmd.imp);
	wait(&temp);
	if (WIFEXITED(temp))
		res = WEXITSTATUS(temp);
	temp = -1;
	while (cmd.argv[++temp])
		free(cmd.argv[temp]);
	free(cmd.argv);
	return (res);
}

char	*get_subshell(char *str)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(str, &itab);
		if (!itab.backslash && !itab.cur_quote && (str[itab.i] == '('))
			itab.ret++;
		else if (!itab.backslash && !itab.cur_quote && (str[itab.i] == ')'))
			itab.ret--;
		if (!itab.ret)
			return (ft_substr(str, 1, itab.i - 1));
	}
	return (ft_substr(str, 1, itab.i - 1));
}

static int	execute_subshell(char *command, t_list **envp, t_main_envp *imp)
{
	char	*name;
	pid_t	pid;
	int		stat;

	pid = fork();
	if (pid < 0)
		return (-1);
	imp->is_bquoted++;
	if (!pid)
	{
		name = get_subshell(command);
		execute_line(split_semicolon(name), envp, imp);
		exit(imp->exit_status);
	}
	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		imp->exit_status = WEXITSTATUS(stat);
	imp->is_bquoted--;
	return (imp->exit_status);
}

static int	execute_command(t_list *commands, t_list **envp, t_main_envp *imp)
{
	if (commands && !commands->next)
	{
		if (((char *)(commands->content))[0] == '(')
			return (execute_subshell((char *)commands->content, envp, imp));
		return (execute_single_command(make_cmd(create_command_argv(
						commands->content, envp, imp), envp, imp)));
	}
	return (execute_pipes(commands, envp, imp));
}

void	execute_line(t_list *commands_list, t_list **envp, t_main_envp *imp)
{
	t_list	*cur_commands;
	t_list	*temp;

	while (commands_list)
	{
		cur_commands = init_pipes((char *)commands_list->content);
		imp->exit_status = execute_command(cur_commands, envp, imp);
		ft_lstclear(&cur_commands, free);
		temp = commands_list;
		commands_list = commands_list->next;
		free(temp->content);
		free(temp);
	}
}
