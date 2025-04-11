/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:06:31 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/11 23:59:01 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void	print_values(t_array occurences, int size, int col, int max)
{
	int		i;
	int		j;
	char	*value;
	int		len;

	printf("\n");
	i = 1;
	while (i < size)
	{
		value = (char *)occurences[i];
		len = ft_strlen(value);
		if (value[len - 1] == '/')
			value[len - 1] = '\0';
		printf("%s", (char *)occurences[i]);
		j = 0;
		while (j < max - len)
		{
			printf(" ");
			j++;
		}
		i++;
		if ((i - 1) % col == 0)
			printf("\n");
	}
	printf("\n");
}

void	display_autocompletion(t_readline_data *data)
{
	t_vector2	tsize;
	int			max;
	int			col;
	int			size;

	if (!data->tab_pressed)
		return ;
	data->tab_pressed = 0;
	size = ft_array_count(data->occurences);
	if (size == 1)
	{
		ft_array_unset(&data->occurences, ft_array_free_entry);
		return ;
	}
	tsize = get_terminal_size(data, 1);
	max = *((int *)data->occurences[0]) + 1;
	col = tsize.x / max;
	print_values(data->occurences, size, col, max);
	data->cursor.y += size / col + 2;
	if (data->cursor.y > tsize.y)
		data->cursor.y = tsize.y;
	ft_array_unset(&data->occurences, ft_array_free_entry);
}
