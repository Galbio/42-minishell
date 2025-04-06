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

	if (!data->actual || data->actual == data->first)
		return ;
	if (!data->actual->next)
		data->actual = data->actual->previous;
	tmp = ft_strdup(data->actual->sequence);
	i = 0;
	while (i < 4)
	{
		data->actual->sequence[i] = data->actual->next->sequence[i];
		i++;
	}
	i = 0;
	while (i < 4)
	{
		data->actual->next->sequence[i] = tmp[i];
		i++;
	}
	data->actual = data->actual->next;
	free(tmp);
	on_write(data);
}
