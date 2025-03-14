/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:30 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/14 13:03:05 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static int	calculate_len(t_readline data, t_char *to)
{
	int		len;
	t_char	*c;

	if (!to)
		return (data.size);
	len = 1;
	c = to;
	while (c->previous)
	{
		len++;
		c = c->previous;
	}
	return (len);
}

char	*build_result(t_readline data, t_char *to)
{
	char	*result;
	t_char	*c;
	int		i;
	int		len;

	if (!data.first || data.first->c == '\n')
		return (ft_strdup(""));
	len = calculate_len(data, to);
	if (!to && data.first && !data.actual)
		return (ft_strdup(""));
	result = malloc(sizeof(char) * (len + 1));
	c = data.first;
	i = 0;
	while (c && (!to || c != to->next))
	{
		result[i] = c->c;
		i++;
		c = c->next;
	}
	result[i] = '\0';
	return (result);
}

int	process_input(t_readline *data, char last_c)
{
	char		*build;
	int			res;

	build = build_result(*data, last_char(data->first));
	res = last_c == '\n' && get_open_quote(build) == 0;
	free(build);
	return (res);
}
