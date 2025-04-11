/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:53:08 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/09 17:19:14 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	add_char_back(t_readline_char *head, t_readline_char *c)
{
	t_readline_char	*cur;

	if (!head || !c)
		return ;
	cur = head;
	while (cur->next)
		cur = cur->next;
	cur->next = c;
	c->previous = cur;
	c->next = NULL;
}

void	add_char_front(t_readline_char **head, t_readline_char *c)
{
	t_readline_char	*tmp;

	if (!c)
		return ;
	if (!*head)
	{
		*head = c;
		return ;
	}
	tmp = *head;
	c->next = tmp;
	tmp->previous = c;
	c->previous = NULL;
	*head = c;
}

void	add_char_after(t_readline_char **element, t_readline_char *c)
{
	t_readline_char	*old_next;

	if (!c)
		return ;
	if (!*element)
	{
		*element = c;
		return ;
	}
	old_next = (*element)->next;
	if (old_next)
		old_next->previous = c;
	c->next = old_next;
	(*element)->next = c;
	c->previous = *element;
}

void	remove_char(t_readline_char **element)
{
	t_readline_char	*previous;
	t_readline_char	*next;

	if (!*element)
		return ;
	previous = (*element)->previous;
	next = (*element)->next;
	if (previous)
		previous->next = next;
	if (next)
		next->previous = previous;
	free(*element);
	if (previous)
		*element = previous;
	else
		*element = next;
}
