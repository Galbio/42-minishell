/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:50:10 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/20 15:54:06 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch(t_list *envp, t_main_envp *imp)
{
	char	*res;
	t_list	*commands;

	ft_readline_set_exit(0);
	init_signals();
	while (1)
	{
		res = ft_readline("$> ");
		if (!res)
			break ;
		if (ft_strchr(res, '`'))
			res = handle_bquotes(res);
		imp->output_fd = 1;
		commands = split_semicolon(res);
		free(res);
		execute_line(commands, &envp, imp);
	}
	free(res);
	printf("\n");
}
