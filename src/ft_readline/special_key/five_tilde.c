/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   five_tilde.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:53:36 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/08 19:14:57 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	five_tilde_key(t_readline_data *data)
{
	process_default_key(data, "5");
	process_default_key(data, "~");
	on_write(data);
}

void	semicolon_five_tilde_key(t_readline_data *data)
{
	process_default_key(data, ";");
	process_default_key(data, "5");
	process_default_key(data, "~");
	on_write(data);
}

void	nofive_buttilde_key(t_readline_data *data)
{
	process_default_key(data, "~");
	on_write(data);
}
