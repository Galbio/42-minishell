/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:17:54 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/21 12:24:52 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	put_contents(char *contents)
{
	int	fd;

	fd = open(HISTORY_PATH, O_CREAT | O_WRONLY, 0644);
	if (!fd)
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

void	save_history(void)
{
	t_readline_core	*core;
	char			**history;
	char			*contents;
	int				total_count;
	int				i;
	int				j;
	int				k;

	core = get_readline_core();
	history = (char **)core->history->content;
	i = core->history->size - 1;
	if (i >= HISTORY_SIZE)
		i = HISTORY_SIZE - 1;
	total_count = count_total_chars(history, i);
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
}
