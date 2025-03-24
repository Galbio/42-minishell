/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:50:10 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/24 17:57:55 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch(t_list *envp, t_main_envp *imp)
{
	char	*res;

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
		imp->input_fd = 0;
		execute_line(res, &envp, imp);
		free(res);
	}
	printf("\n");
}
