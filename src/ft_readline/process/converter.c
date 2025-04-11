/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:12:30 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/11 23:55:41 by lroussel         ###   ########.fr       */
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

static t_readline_char	*paste_on(char **result, t_readline_char *c,
	int *i, int incr)
{
	int	j;

	j = 0;
	while (c->sequence[j])
	{
		(*result)[*i + j] = c->sequence[j];
		j++;
	}
	*i += incr * j;
	if (incr > 0)
		return (c->next);
	return (c->previous);
}

char	*list_to_string(t_readline_data data, t_readline_char *to)
{
	char			*result;
	t_readline_char	*cur;
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
	cur = data.first;
	i = 0;
	while (cur && (!to || cur != to->next))
		cur = paste_on(&result, cur, &i, 1);
	return (result);
}

int	is_first_argument(t_readline_char *position)
{
	t_readline_char	*cur;

	if (!position)
		return (1);
	cur = position;
	while (cur && !ft_strchr(" \t\n;&|", cur->sequence[0]))
		cur = cur->previous;
	return (!cur);
}

char	*get_argument_before(t_readline_char *position)
{
	int				i;
	t_readline_char	*cur;
	char			*result;

	if (!position)
		return (NULL);
	cur = position;
	i = 0;
	while (cur && !ft_strchr(" \t\n;&|", cur->sequence[0]))
	{
		i += ft_strlen(cur->sequence);
		cur = cur->previous;
	}
	if (i == 0)
		return (NULL);
	cur = position;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	result[i] = '\0';
	i--;
	while (i >= 0)
		cur = paste_on(&result, cur, &i, -1);
	return (result);
}
