/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:33:57 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/05 19:36:59 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int	get_extra_data_in_fd(void)
{
	if (!isatty(STDIN_FILENO))
		return (STDERR_FILENO);
	return (STDIN_FILENO);
}

int	get_extra_data_out_fd(void)
{
	if (!isatty(STDOUT_FILENO))
		return (STDERR_FILENO);
	return (STDOUT_FILENO);
}
