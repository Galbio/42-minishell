/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslashes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:16:47 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 14:17:14 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static int	new_size(char *build, int old_size)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < old_size)
	{
		if ((i + 3 <= old_size) && (ft_strncmp(build + i, "\\\n", 2) == 0))
			i += 2;
		len++;
		i++;
	}
	return (len);
}

char	*clean_backslashes(char *build)
{
	char	*res;
	int		i;
	int		j;
	int		old_size;

	old_size = ft_strlen(build);
	res = malloc((new_size(build, old_size) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < old_size)
	{
		if ((i + 3 <= old_size) && (ft_strncmp(build + i, "\\\n", 2) == 0))
			i += 2;
		res[j] = build[i];
		j++;
		i++;
	}
	res[j] = '\0';
	free(build);
	return (res);
}
