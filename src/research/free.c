/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 01:08:38 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/09 01:09:49 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_regex_match(t_research *regex)
{
	void	*temp;

	while (regex)
	{
		temp = regex;
		ft_lstclear(&regex->matches, free);
		regex = regex->next;
		free(temp);
	}
}
