/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:22:26 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/26 16:55:13 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static char	*hpath(char *value)
{
	static char	*path = ".";

	if (value)
		path = value;
	return (path);
}

void	set_history_path(char *value)
{
	hpath(value);
}

char	*get_history_path(void)
{
	return (hpath(NULL));
}

char	*get_history_path_full(void)
{
	return (ft_pathjoin(get_history_path(), get_history_filename()));
}
