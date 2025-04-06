/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:17:54 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/26 20:25:54 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void	put_contents(char *contents, int size)
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
	write(fd, contents, size);
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
	char	*contents;
	int		j;
	int		k;
	int		size;

	size = total_count + i;
	contents = malloc((size + 1) * sizeof(char));
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
	put_contents(contents, size);
	free(contents);
}

void	save_history(void)
{
	t_readline	*main;
	char		**history;
	int			i;

	if (!is_history_enable())
		return ;
	main = get_readline_struct();
	history = (char **)main->history;
	i = ft_array_count(main->history) - 1;
	if (i >= get_history_maxsize())
		i = get_history_maxsize() - 1;
	save_contents(history, count_total_chars(history, i), i);
}
