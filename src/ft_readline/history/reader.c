/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:08:19 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/26 16:51:08 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void	parse_history(const char *content, t_readline *core)
{
	char	**values;
	int		i;

	values = ft_split(content, '\n');
	if (!values)
		return ;
	i = 0;
	while (values[i])
	{
		if (ft_strlen(values[i]) == 0)
			free(values[i]);
		ft_array_unshift(&core->history, values[i]);
		i++;
	}
	free(values);
}

void	init_history(void)
{
	char		*contents;
	t_readline	*core;

	core = get_readline_core();
	core->history = ft_array();
	contents = get_history_file_contents();
	if (!contents)
		return ;
	parse_history(contents, core);
	free(contents);
}

char	*get_history_file_contents(void)
{
	char	*path;
	int		fd;
	char	*contents;

	path = get_history_path_full();
	if (!path)
		return (NULL);
	fd = open(path, O_RDONLY);
	free(path);
	if (fd == -1)
		return (NULL);
	contents = ft_get_contents(fd);
	close(fd);
	return (contents);
}
