/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:30 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/05 10:25:22 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char	*build_result(t_readline data, int to_actual)
{
	char	*result;
	t_char	*c;
	int		i;
	int	len;

	if (!data.first || data.first->c == '\n')
		return (ft_strdup(""));
	len = data.size;
	if (to_actual)
	{
		len = 0;
		c = data.first;
		if (!data.actual)
			return (ft_strdup(""));
		while (c && c != data.actual->next)
		{
			len++;
			c = c->next;
		}
	}
	result = malloc(sizeof(char) * (len + 1));
	c = data.first;
	i = 0;
	while (c && (!to_actual || c != data.actual->next))
	{
		result[i] = c->c;
		i++;
		c = c->next;
	}
	result[i] = '\0';
	return (result);
}

int	process_input(t_readline *data, char *buffer)
{
	char		*build;

	build = build_result(*data, 0);
	if (buffer[0] == '\n' && get_open_quote(build) == 0)
	{
		write(1, "\n", 1);
		return (1);
	}
	free(build);
	return (0);
}
