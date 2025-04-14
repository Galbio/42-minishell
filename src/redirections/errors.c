/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:04:14 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/14 08:04:10 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_file_errors(char **values, char *og_str)
{
	char	*temp;
	char	*save;

	if (values[1])
		return (display_error("minishell: ",
				og_str, ": ambiguous redirect\n", 1));
	if (ft_strlen(values[0]) > 255)
		return (display_error("minishell: ",
				values[0], ": File name too long\n", 1));
	if (ft_isdir(values[0]))
		return (display_error("minishell: ",
				values[0], ": Is a directory\n", 1));
	save = ft_strrchr(values[0], '/');
	if (save)
	{
		temp = ft_substr(values[0], 0, save - values[0]);
		if (ft_canaccess(temp) == -1)
		{
			free(temp);
			return (display_error("minishell: ",
					values[0], ": No such file or directory\n", 1));
		}
		free(temp);
	}
	return (0);
}
