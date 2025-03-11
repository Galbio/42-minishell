/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:30 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/10 15:50:18 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

char	*build_result(t_readline data)
{
	char	*result;
	t_char	*c;
	int		i;

	if (!data.first || data.first->c == '\n')
		return (ft_strdup(""));
	result = malloc(sizeof(char) * (data.size + 1));
	c = data.first;
	i = 0;
	while (c)
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

	build = build_result(*data);
	if (buffer[0] == '\n' && get_open_quote(build) == 0)
	{
		write(1, "\n", 1);
		free(build);
		return (1);
	}
	if (buffer[0] == '\n')
		write(1, "\n", 1);
	free(build);
	return (0);
}
