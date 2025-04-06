/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:30 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 15:37:05 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_readline_keys.h"

static int	calculate_len(t_readline_data data, t_readline_char *to)
{
	int				len;
	t_readline_char	*c;

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

static void	paste_on(char **result, t_readline_char *c, int *i)
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

char	*list_to_string(t_readline_data data, t_readline_char *to)
{
	char			*result;
	t_readline_char	*c;
	int				i;
	int				len;

	if (!data.first || (data.first->c[0] == '\n' && !data.first->next))
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
