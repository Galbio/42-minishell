/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:50:10 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/23 06:42:00 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch(void)
{
	char	*res;

	while (1)
	{
		res = ft_readline("$> ");
		if (clean_readed(&res))
			; //TODO: parse with res
		free(res);
	}
}
