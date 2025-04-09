/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:50:10 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/09 20:42:43 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_readline_keys.h"

static void	init(char *home)
{
	ft_readline_set_exit(0);
	set_history_path(home);
	set_history_filename(".minishell_history");
	enable_history();
	ft_readline_register_event(CTRL_C_KEY, on_sigint);
	init_signals();
	init_regexs();
}

static void	init_execution(t_list *envp, t_main_envp *imp, t_list **cmds)
{
	char	*res;

	set_exit_status(0);
	imp->output_fd = 1;
	imp->input_fd = 0;
	imp->actual_pos = 0;
	imp->heredocs_infos = NULL;
	res = identify_heredoc((*cmds)->content, cmds, imp);
	if (ft_strchr(res, '`'))
		res = handle_bquotes(res);
	execute_line(res, &envp, imp);
}

void	launch(t_list *envp, t_main_envp *imp)
{
	char	*res;
	t_list	*cmds;

	init(imp->home);
	while (1)
	{
		cmds = NULL;
		res = ft_readline("$> ");
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
	write(STDIN_FILENO, "\n", 1);
}
