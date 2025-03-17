/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:30 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/17 16:23:39 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "readline_keys.h"

static int	calculate_len(t_readline data, t_char *to)
{
	int		len;
	t_char	*c;

	if (!to)
	{
		if (!data.first)
			return (0);
		c = data.first;
		len = ft_strlen(c->c);
		while (c->next)
		{
			len += ft_strlen(c->c);
			c = c->next;
		}
		return (len);
	}
	len = ft_strlen(to->c);
	c = to;
	while (c->previous)
	{
		len += ft_strlen(c->c);
		c = c->previous;
	}
	return (len);
}

static void	paste_on(char **result, t_char *c, int *i)
{
	int		j;

	j = 0;
	while (c->c[j])
	{
		(*result)[*i] = c->c[j];
		j++;
		(*i)++;
	}
}

char	*build_result(t_readline data, t_char *to)
{
	char	*result;
	t_char	*c;
	int		i;
	int		len;

	if (!data.first || data.first->c[0] == '\n')
		return (ft_strdup(""));
	len = calculate_len(data, to);
	if (!to && data.first && !data.actual)
		return (ft_strdup(""));
	result = malloc(sizeof(char) * (len + 2));
	ft_bzero(result, len + 2);
	c = data.first;
	i = 0;
	while (c && (!to || c != to->next))
	{
		paste_on(&result, c, &i);
		c = c->next;
	}
	return (result);
}

int	process_input(t_readline *data, char last_c)
{
	char		*build;
	int			res;

	build = build_result(*data, last_char(data->first));
	res = (last_c == '\n' || last_c == CTRL_O_KEY[0])
		&& get_open_quote(build) == 0;
	free(build);
	return (res);
}
