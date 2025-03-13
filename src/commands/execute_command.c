/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:04:40 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/13 02:06:28 by gakarbou         ###   ########.fr       */
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

static void	execute_command(t_list *commands, t_list **envp, t_main_envp *imp)
{
	pid_t			pid;
	int				code;
	t_cmd_params	cmd;

	if (commands && !commands->next)
	{
		cmd = make_cmd(commands->content, envp, imp);
		code = check_builtins(cmd.argv[0]);
		if (code)
			handle_builtins(code, &cmd);
		else
		{
			pid = fork();
			if (pid < 0)
				return ;
			if (!pid)
				execute_bin(cmd.argv, cmd.imp);
			wait(&code);
		}
		return ;
	}
	else
		execute_pipes(commands, envp, imp);
}

void	execute_line(t_list *commands_list, t_list **envp, t_main_envp *imp)
{
	t_list	*temp;
	t_list	*cur_commands;

	while (commands_list)
	{
		cur_commands = init_pipes((char *)commands_list->content, envp, imp);
		execute_command(cur_commands, envp, imp);
		free_cur_commands(cur_commands);
		temp = commands_list;
		commands_list = commands_list->next;
		free(temp->content);
		free(temp);
	}
}
