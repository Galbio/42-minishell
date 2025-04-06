/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:19:01 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/15 20:00:46 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	backspace_key(t_readline_data *data)
{
	if (!data->first)
		return ;
	if (data->current == data->first)
	{
		data->first = data->first->next;
		remove_char(&data->current);
		data->current = NULL;
		on_delete(data);
		return ;
	}
	remove_char(&data->current);
	on_delete(data);
}

void	delete_key(t_readline_data *data)
{
	t_readline_char	*tmp;

	if (!data->first || (data->current && !data->current->next))
		return ;
	if (data->first && !data->current)
	{
		tmp = data->first->next;
		remove_char(&data->first);
		data->first = tmp;
		on_delete(data);
		return ;
	}
	if (data->current->next)
	{
		data->current = data->current->next;
		remove_char(&data->current);
		on_delete(data);
	}
}
