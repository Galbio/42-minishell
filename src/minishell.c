/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:50:10 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/06 07:37:42 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(void)
{
	struct termios	raw;

	enable_raw_mode(&raw);
}

void	launch(t_list *envp, t_main_envp *imp)
{
	t_list	*commands;
	char	*res;

	init();
	while (1)
	{
		res = ft_readline("$> ");
		if (!res)
			break ;
		if (!clean_readed(&res))
		{
			free(res);
			continue ;
		}
		commands = init_pipes(res, &envp, imp);
		free(res);
		execute_line(commands, &envp, imp);
	}
	printf("\n");
}
