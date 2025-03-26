/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:17:54 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/26 16:50:48 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	put_contents(char *contents)
{
	char	*path;
	int		fd;

	path = get_history_path_full();
	if (!path)
		return ;
	unlink(path);
	fd = open(path, O_CREAT | O_WRONLY, 0644);
	free(path);
	if (fd == -1)
		return ;
	write(fd, contents, ft_strlen(contents));
}

static int	count_total_chars(char **history, int key)
{
	int	i;
	int	count;

	i = key;
	count = 0;
	while (i >= 0)
	{
		count += ft_strlen(history[i]);
		i--;
	}
	return (count);
}

static void	save_contents(char **history, int total_count, int i)
{
	char			*contents;
	int				j;
	int				k;

	contents = malloc((total_count + i + 1) * sizeof(char));
	if (!contents)
		return ;
	k = 0;
	while (i >= 0)
	{
		j = 0;
		while (history[i][j])
			contents[k++] = history[i][j++];
		i--;
		if (i >= 0)
			contents[k++] = '\n';
	}
	contents[k] = '\0';
	put_contents(contents);
	free(contents);
}

void	save_history(void)
{
	t_readline_core	*core;
	char			**history;
	int				i;

	core = get_readline_core();
	history = (char **)core->history;
	i = ft_array_count(core->history) - 1;
	if (i >= HISTORY_SIZE)
		i = HISTORY_SIZE - 1;
	save_contents(history, count_total_chars(history, i), i);
}
