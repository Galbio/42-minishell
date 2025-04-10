/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:46:31 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 15:48:03 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	swap_key(t_readline_data *data)
{
	char		*tmp;
	int			i;

	if (!data->current || data->current == data->first)
		return ;
	if (!data->current->next)
		data->current = data->current->previous;
	tmp = ft_strdup(data->current->sequence);
	i = 0;
	while (i < 4)
	{
		data->current->sequence[i] = data->current->next->sequence[i];
		i++;
	}
	i = 0;
	while (i < 4)
	{
		data->current->next->sequence[i] = tmp[i];
		i++;
	}
	data->current = data->current->next;
	free(tmp);
	on_write(data);
}
