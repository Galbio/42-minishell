/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:06:31 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/10 17:06:29 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	display_autocomplatable_commands(char *prefix)
{
	(void)prefix;
	int	i;
	char	***path;
	t_array	values;
	int	j;
	int	len;
	int	size;
	char	*value;
	int	count = 0;

	path = ft_readline_get_path_ptr();
	if (!path || !(*path))
		return ;
	i = 0;
	if (prefix)
		len = ft_strlen(prefix);
	else
		len = 0;
	while ((*path)[i])
	{
		values = ft_scandir((*path)[i], SCANDIR_SORT_NONE, 0, 0);
		size = ft_array_count(values);
		i++;
		j = 0;
		while (j < size)
		{
			value = ft_pathjoin((*path)[i], (char *)values[j]);
			if (access(value, X_OK) && (len == 0 || ft_strncmp((char *)values[j], prefix, len) == 0) && !ft_isdir(value))
			{
				count++;
				printf("%s ", (char *)values[j]);
			}
			free(value);
			free((char *)values[j]);
			j++;
		}
		ft_array_unset(&values, ft_array_nothing_entry);
	}
	printf("%i\n", count);
}
