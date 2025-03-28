/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:50:10 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/27 04:11:41 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init(char *home)
{
	ft_readline_set_exit(0);
	init_signals();
	set_history_path(home);
	set_history_filename(".minishell_history");
	enable_history();
}

void	launch(t_list *envp, t_main_envp *imp)
{
	char	*res;

	init(imp->home);
	while (1)
	{
		res = ft_readline("$> ");
		if (!res)
			break ;
		if (ft_strlen(res) >= 1)
			add_to_history(res);
		if (ft_isonlywhitespaces(res))
		{
			free(res);
			continue ;
		}
		if (ft_strchr(res, '`'))
			res = handle_bquotes(res);
		imp->output_fd = 1;
		imp->input_fd = 0;
		execute_line(res, &envp, imp);
	}
	write(1, "\n", 1);
}
