/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:50:10 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/27 14:30:50 by gakarbou         ###   ########.fr       */
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
	char	*res;
	char	*str;

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
		str = parse_commands(res, envp, imp);
		if (str)
			(printf("%s", str), free(str));
	}
	printf("\n");
}
