/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:50:10 by lroussel          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/05 17:00:18 by gakarbou         ###   ########.fr       */
=======
/*   Updated: 2025/03/05 16:55:49 by gakarbou         ###   ########.fr       */
>>>>>>> refs/heads/main
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
