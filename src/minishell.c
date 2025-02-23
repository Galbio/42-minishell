/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:50:10 by lroussel          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/02/23 13:43:52 by gakarbou         ###   ########.fr       */
=======
/*   Updated: 2025/02/23 13:50:35 by lroussel         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< Updated upstream
void	launch(t_list *envp, t_main_envp *imp)
=======
void	init(void)
{
	struct termios	raw;

	enable_raw_mode(&raw);
}

void	launch(void)
>>>>>>> Stashed changes
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
			(printf("%s\n", str), free(str));
	}
	printf("\n");
}
