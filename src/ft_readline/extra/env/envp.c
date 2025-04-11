/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:09:33 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/11 21:05:22 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static t_list	***senv(t_list ***v, int update)
{
	static t_list	***envp = NULL;

	if (update == 1)
		envp = v;
	return (envp);
}

void	ft_readline_set_envp_ptr(t_list ***envp)
{
	senv(envp, 1);
}

t_list	***ft_readline_get_envp_ptr(void)
{
	return (senv(NULL, 0));
}
