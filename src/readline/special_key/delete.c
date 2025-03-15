/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:19:01 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/15 19:42:55 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	on_press_backspace_key(t_readline *data)
{
	if (!data->first)
		return ;
	if (data->actual == data->first)
	{
		data->first = data->first->next;
		remove_char(&data->actual);
		data->actual = NULL;
		on_delete(data);
		return ;
	}
	remove_char(&data->actual);
	on_delete(data);
}

void	on_press_delete_key(t_readline *data)
{
	t_char	*tmp;

	if (!data->first || (data->actual && !data->actual->next))
		return ;
	if (data->first && !data->actual)
	{
		tmp = data->first->next;
		remove_char(&data->first);
		data->first = tmp;
		on_delete(data);
		return ;
	}
	if (data->actual->next)
	{
		data->actual = data->actual->next;
		remove_char(&data->actual);
		on_delete(data);
	}
}
