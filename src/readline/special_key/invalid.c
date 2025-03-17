/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 23:06:49 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/17 11:49:02 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	invalid_key(t_readline *data)
{
	(void)data;
}

void	five_tilde_key(t_readline *data)
{
	process_default_key(data, "5");
	process_default_key(data, "~");
	on_write(data);
}
