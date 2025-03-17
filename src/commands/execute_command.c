/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:04:40 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/17 20:04:50 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cur_commands(t_list *commands)
{
	t_list	*temp;
	char	**argv;
	int		i;

	while (commands)
	{
		i = -1;
		argv = (char **)commands->content;
		while (argv[++i])
			free(argv[i]);
		free(argv);
		temp = commands;
		commands = commands->next;
		free(temp);
	}
	return ;
}

static int	execute_builtins(int code, t_cmd_params cmd)
{
	pid_t		pid;
	int			res;
	int			stat;

	res = cmd.imp->exit_status;
	if (cmd.imp->is_bquoted)
	{
		pid = fork();
		if (pid < 0)
			return (1);
		if (!pid)
		{
			dup2(cmd.imp->output_fd, 1);
			res = handle_builtins(code, &cmd);
			free_envp(cmd.envp, cmd.imp);
			exit(res);
		}
		waitpid(pid, &stat, 0);
		if (WIFEXITED(stat))
			res = WEXITSTATUS(stat);
	}
	else
		res = handle_builtins(code, &cmd);
	return (res);
}

static int	execute_single_command(t_cmd_params cmd)
{
	pid_t		pid;
	int			code;
	int			res;

	res = cmd.imp->exit_status;
	code = check_builtins(cmd.argv[0]);
	if (code)
		res = execute_builtins(code, cmd);
	else if (cmd.argv[0][0])
	{
		pid = fork();
		if (pid < 0)
			return (1);
		if (!pid)
		{
			dup2(cmd.imp->output_fd, 1);
			execute_bin(cmd.argv, cmd.imp);
		}
		wait(&code);
		if (WIFEXITED(code))
			res = WEXITSTATUS(code);
	}
	return (res);
}

static int	execute_command(t_list *commands, t_list **envp, t_main_envp *imp)
{
	if (commands && !commands->next)
		return (execute_single_command(make_cmd(commands->content, envp, imp)));
	return (execute_pipes(commands, envp, imp));
}

void	execute_line(t_list *commands_list, t_list **envp, t_main_envp *imp)
{
	t_list	*temp;
	t_list	*cur_commands;

	while (commands_list)
	{
		cur_commands = init_pipes((char *)commands_list->content, envp, imp);
		imp->exit_status = execute_command(cur_commands, envp, imp);
		free_cur_commands(cur_commands);
		temp = commands_list;
		commands_list = commands_list->next;
		free(temp->content);
		free(temp);
	}
}
