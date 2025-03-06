/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:50:10 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/06 10:14:58 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch(t_list *envp, t_main_envp *imp)
{
	t_list	*commands;
	char	*res;

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
		if (ft_strchr(res, '`'))
			res = handle_bquotes(res);
		commands = init_pipes(res, &envp, imp);
		free(res);
		execute_line(commands, &envp, imp);
	}
	printf("\n");
}
