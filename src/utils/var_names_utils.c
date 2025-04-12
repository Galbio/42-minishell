/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_names_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:16:32 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/12 18:12:04 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_to_var_end(char *str)
{
	int		i;

	if (ft_strchr("{(", str[0]))
		return (get_subcmd_size(str + 1) + 0);
	if (ft_strchr("{(", str[1]))
		return (get_subcmd_size(str + 1) + 1);
	if (ft_strchr("?#", str[1]) || ft_isdigit(str[1]))
		return (2);
	i = 0;
	while (str[++i])
		if ((str[i] != '_') && !ft_isalnum(str[i]))
			return (i);
	return (i);
}

char	*get_var_name(char *str)
{
	int		i;

	if (ft_isdigit(*str))
		return (ft_itoa(*str + '0'));
	if (*str == '?')
		return (ft_strdup("?"));
	if (*str == '#')
		return (ft_strdup("#"));
	i = -1;
	while (str[++i])
		if ((str[i] != '_') && !ft_isalnum(str[i]))
			return (ft_substr(str, 0, i));
	return (ft_substr(str, 0, i + 1));
}
