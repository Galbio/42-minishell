/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_aliases.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:26:54 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/09 13:52:22 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_aliases(char *input, t_list *aliases)
{
	char	*alias;
	int		len;

	if (!aliases)
		return (NULL);
	len = 0;
	while (input[len] && !ft_strchr(" \t", input[len]))
		len++;
	while (aliases)
	{
		alias = (char *)aliases->content;
		if (!ft_strncmp(alias, input, len) && (alias[len] == '='))
			return (ft_strreplace_part(input, 0, len, alias + len + 1));
		aliases = aliases->next;
	}
	return (NULL);
}
