/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:53:50 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/15 21:36:17 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_char	*new_char(char c[4])
{
	t_char	*res;
	int		i;

	res = malloc(sizeof(t_char));
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

t_char	*last_char(t_char *head)
{
	t_char	*cur;

	if (!head)
		return (NULL);
	cur = head;
	while (cur->next)
		cur = cur->next;
	return (cur);
}

void	free_chars(t_char *head)
{
	t_char	*cur;
	t_char	*tmp;
	
	cur = head;
	while (cur)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
}
