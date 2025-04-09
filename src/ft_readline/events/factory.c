/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:31:17 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/09 20:08:08 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	ft_readline_register_event(char *sequence,
	void (*callback)(t_readline_data *))
{
	t_readline_event	*new;

	new = malloc(sizeof(t_readline_event));
	if (!new)
		return ;
	new->sequence = sequence;
	new->callback = callback;
	ft_lstadd_back(&(get_readline_struct()->events), ft_lstnew(new));
}

int	ft_readline_execute_events(t_readline_data *data, char *sequence)
{
	t_list				*events;
	t_readline_event	*event;
	int					max;
	int					len;

	events = get_readline_struct()->events;
	max = 0;
	while (events)
	{
		event = (t_readline_event *)(events->content);
		len = ft_strlen(event->sequence);
		if (ft_strncmp(sequence, event->sequence,
				ft_max(ft_strlen(sequence), len)) == 0)
		{
			(event->callback)(data);
			if (len > max)
				max = len;
		}
		events = events->next;
	}
	return (max);
}
