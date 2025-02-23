/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:53:50 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/23 19:53:50 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_char	*new_char(int c)
{
	t_char	*res;

	res = malloc(sizeof(t_char));
	res->c = c;
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
