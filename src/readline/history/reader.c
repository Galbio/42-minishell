/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:08:19 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/21 12:27:03 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	parse_history(const char *content, t_readline_core *core)
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
		ft_array_unshift(core->history, &values[i]);
		i++;
	}
	free(values);
}

void	init_history(void)
{
	const char	*content;
	t_readline_core *core;

	core = get_readline_core();
	core->history = ft_array(STRING, sizeof(char *));
	content = get_history_file_contents();
	if (!content)
		return ;
	parse_history(content, core);
}

const char	*get_history_file_contents(void)
{
	int			fd;
	const char	*content;

	fd = open(HISTORY_PATH, O_RDONLY);
	if (fd == -1)
		return (NULL);
	content = ft_get_contents(fd);
	close(fd);
	return (content);
}
