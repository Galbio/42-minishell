/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:49:17 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/04 21:49:20 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_argument(char *value)
{
	int	i;

	if (!value || !value[0])
		return (NULL);
	i = 0;
	while (value[i] && value[i] != ' ' && value[i] != '\t' && value[i] != '\n'
		&& value[i] != ';' && value[i] != '&' && value[i] != '|')
		i++;
	return (ft_substr(value, 0, i));
}

static void	update_list(t_research **cur, t_research **head,
	char *addr, char *argument)
{
	char		**splited;
	int			i;

	if (!(*cur))
	{
		*head = malloc(sizeof(t_research));
		*cur = *head;
	}
	else
	{
		(*cur)->next = malloc(sizeof(t_research));
		*cur = (*cur)->next;
	}
	(*cur)->next = NULL;
	(*cur)->addr = addr;
	(*cur)->len = ft_strlen(argument);
	splited = ft_split(argument, '/');
	(*cur)->matches = search_pattern_recursive(".", splited);
	i = 0;
	while (splited[i])
		free(splited[i++]);
	free(splited);
}

//TODO: quotes (\' \")
t_research	*parse_research(char *value)
{
	int			i;
	int			len;
	char		*argument;
	t_research	*research;
	t_research	*cur;

	i = 0;
	len = ft_strlen(value);
	research = NULL;
	cur = NULL;
	while (i < len)
	{
		while (value[i] && ft_strchr(" \t\n;&|", value[i]))
			i++;
		if (i >= len)
			break ;
		argument = find_argument(value + i);
		if (ft_strchr(argument, '*') || ft_strchr(argument, '?')
			|| ft_strchr(argument, '['))
			update_list(&cur, &research, value + i, argument);
		i += ft_strlen(argument) + 1;
		free(argument);
	}
	return (research);
}
