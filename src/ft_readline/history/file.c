/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:26:05 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/26 17:15:24 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static char	*hname(char *value)
{
	static char	*name = ".rl_history";

	if (value)
		name = value;
	return (name);
}

void	set_history_filename(char *name)
{
	hname(name);
}

char	*get_history_filename(void)
{
	return (hname(NULL));
}
