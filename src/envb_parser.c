/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envb_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:57:32 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/23 00:34:47 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parse_envp(char **envp)
{
	t_list	*dest;
	int		i;

	if (!envp || !envp[0])
		return (NULL);
	i = 0;
	dest = ft_lstnew(ft_strdup(envp[0]));
	while (env[++i])
	{
		ft_lstadd_front(
	}
}
