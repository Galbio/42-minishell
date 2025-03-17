/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   five_tilde.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:53:36 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/17 17:55:49 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	five_tilde_key(t_readline *data)
{
	process_default_key(data, "5");
	process_default_key(data, "~");
	on_write(data);
}

void	semicolon_five_tilde_key(t_readline *data)
{
	process_default_key(data, ";");
	process_default_key(data, "5");
	process_default_key(data, "~");
	on_write(data);
}
