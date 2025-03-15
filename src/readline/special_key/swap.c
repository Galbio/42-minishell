/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:46:31 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/15 21:25:17 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	swap_key(t_readline *data)
{
	char		*tmp;
	int	i;

	if (!data->actual || data->actual == data->first)
		return ;
	if (!data->actual->next)
		data->actual = data->actual->previous;
	tmp = ft_strdup(data->actual->c);
	i = 0;
	while (i < 4)
	{
		data->actual->c[i] = data->actual->next->c[i];
		i++;
	}
	i = 0;
	while (i < 4)
	{
		data->actual->next->c[i] = tmp[i];
		i++;
	}
	data->actual = data->actual->next;
	free(tmp);
	on_write(data);
}
