/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:30 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/09 14:09:17 by lroussel         ###   ########.fr       */
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
		len = ft_strlen(c->sequence);
		while (c->next)
		{
			len += ft_strlen(c->sequence);
			c = c->next;
		}
		return (len);
	}
	len = ft_strlen(to->sequence);
	c = to;
	while (c->previous)
	{
		len += ft_strlen(c->sequence);
		c = c->previous;
	}
	return (len);
}

static void	paste_on(char **result, t_readline_char *c, int *i)
{
	int		j;

	j = 0;
	while (c->sequence[j])
	{
		(*result)[*i + j] = c->sequence[j];
		j++;
	}
	*i += j;
}

char	*list_to_string(t_readline_data data, t_readline_char *to)
{
	char			*result;
	t_readline_char	*c;
	int				i;
	int				len;

	if (!data.first || (data.first->sequence[0] == '\n' && !data.first->next))
		return (ft_strdup(""));
	len = calculate_len(data, to);
	if (!to && data.first && !data.current)
		return (ft_strdup(""));
	result = malloc(sizeof(char) * (len + 2));
	if (!result)
		return (NULL);
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
