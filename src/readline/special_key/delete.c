/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:19:01 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/14 14:20:58 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	on_press_delete_key(t_readline *data)
{
	t_char	*c;

	if (!data->actual || data->size <= 0)
		return ;
	if (data->actual == data->first)
	{
		data->first = data->first->next;
		remove_char(&data->actual);
		data->actual = NULL;
		on_delete(data);
		return ;
	}
	c = data->actual;
	remove_char(&data->actual);
	if (data->actual != c)
		data->size--;
	if (!data->actual && data->size == 0)
		data->first = NULL;
	on_delete(data);
}
