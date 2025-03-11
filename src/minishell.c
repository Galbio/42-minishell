/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:50:10 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/05 16:43:39 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch(t_list *envp, t_main_envp *imp)
{
	char	*res;
	char	*str;

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
		str = execute_command(res, &envp, imp);
		free(res);
		if (str)
		{
			write(1, str, ft_strlen(str));
			free(str);
		}
	}
	printf("\n");
}
