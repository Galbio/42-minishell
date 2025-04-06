/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:53:08 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/23 18:21:12 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	add_char_back(t_char *head, t_char *c)
{
	t_char	*cur;

	if (!head || !c)
		return ;
	cur = head;
	while (cur->next)
		cur = cur->next;
	cur->next = c;
	c->previous = cur;
	c->next = NULL;
}

void	add_char_front(t_char **head, t_char *c)
{
	t_char	*tmp;

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

void	add_char_after(t_char **element, t_char *c)
{
	t_char	*old_next;

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

void	add_char_before(t_char *element, t_char *c)
{
	t_char	*old_previous;

	if (!element || !c)
		return ;
	old_previous = element->previous;
	if (old_previous)
		old_previous->next = c;
	c->previous = old_previous;
	element->previous = c;
	c->next = element;
}

void	remove_char(t_char **element)
{
	t_char	*previous;
	t_char	*next;

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
