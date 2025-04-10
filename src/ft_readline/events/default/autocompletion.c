/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:23:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/10 18:13:28 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	tab_key(t_readline_data *data)
{
	char	*value;

	if (data->first == NULL)
		return ;
	if (data->tab_pressed)
	{
		value = get_argument_before(data->current);
		display_autocomplatable_commands(value);
		free(value);
	}	
	data->tab_pressed = !data->tab_pressed;
}
