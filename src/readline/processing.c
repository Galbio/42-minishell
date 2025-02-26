/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:30 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/26 13:32:25 by lroussel         ###   ########.fr       */
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

int	process_input(t_readline *data)
{
	char		*build;

	build = build_result(*data);
	if (data->c == '\n' && check_quotes(build) && check_backslashs(build))
	{
		write(1, "\n", 1);
		return (1);
	}
	if (data->c == '\n')
		write(1, "\n", 1);
	free(build);
	return (0);
}
