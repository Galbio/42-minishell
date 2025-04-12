/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:50:10 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/12 22:36:44 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_readline_keys.h"

static void	init(t_main_envp *imp, t_list **envp)
{
	ft_readline_set_exit(0);
	ft_readline_set_path_ptr(&imp->path);
	ft_readline_set_envp_ptr(envp);
	set_history_path(imp->home);
	set_history_filename(".minishell_history");
	enable_history();
	ft_readline_register_event(CTRL_C_KEY, on_sigint);
	init_signals();
	init_regexs();
	set_exit_status(0);
}

static void	init_execution(t_list *envp, t_main_envp *imp, t_list **cmds)
{
	t_list	*temp;
	char	*res;
	int		exit_status;

	if ((*cmds)->content == NULL)
	{
		temp = *cmds;
		*cmds = temp->next;
		free(temp);
		return ;
	}
	imp->output_fd = 1;
	imp->input_fd = 0;
	imp->actual_pos = 0;
	imp->heredocs_infos = NULL;
	imp->cmd_queue = (*cmds)->next;
	exit_status = get_exit_status();
	if (exit_status >= 256)
		set_exit_status(exit_status - 256);
	ft_readline_set_check_format(0);
	res = identify_heredoc((*cmds)->content, cmds, imp);
	ft_readline_set_check_format(1);
	if (ft_strchr(res, '`'))
		res = handle_bquotes(res);
	execute_line(res, &envp, imp);
}

void	launch(t_list *envp, t_main_envp *imp)
{
	char	*prompt;
	char	*res;
	t_list	*cmds;

	init(imp, &envp);
	while (1)
	{
		cmds = NULL;
		prompt = get_prompt(imp);
		res = ft_readline(prompt);
		free(prompt);
		if (!res)
			break ;
		if (ft_isonlywhitespaces(res))
		{
			free(res);
			continue ;
		}
		split_cmds(res, &cmds);
		free(res);
		while (cmds)
			init_execution(envp, imp, &cmds);
	}
	free_readline();
	write(STDOUT_FILENO, "\nexit\n", 6);
}
