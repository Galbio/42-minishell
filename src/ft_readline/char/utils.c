/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:53:50 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 15:36:00 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

t_readline_char	*new_char(char c[4])
{
	t_readline_char	*res;
	int				i;

	res = malloc(sizeof(t_readline_char));
	if (!res)
		return (NULL);
	i = 0;
	while (i != 4)
	{
		res->c[i] = c[i];
		i++;
	}
	res->previous = NULL;
	res->next = NULL;
	return (res);
}

t_readline_char	*last_char(t_readline_char *head)
{
	t_readline_char	*cur;

	if (!head)
		return (NULL);
	cur = head;
	while (cur->next)
		cur = cur->next;
	return (cur);
}

void	free_chars(t_readline_char *head)
{
	t_readline_char	*cur;
	t_readline_char	*tmp;

	cur = head;
	while (cur)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
}
