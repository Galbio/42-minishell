/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:20:43 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/11 20:21:34 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static char	***spath(char ***v, int update)
{
	static char	***path = NULL;

	if (update == 1)
		path = v;
	return (path);
}

void	ft_readline_set_path_ptr(char ***path)
{
	spath(path, 1);
}

char	***ft_readline_get_path_ptr(void)
{
	return (spath(NULL, 0));
}
