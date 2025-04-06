/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_position.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:10:32 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/05 21:56:09 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char	*last_newline(char *build)
{
	char	*newline;
	int		i;

	newline = build;
	i = 0;
	while (build[i])
	{
		if (build[i] && build[i] == '\n')
			newline = build + i + 1;
		i++;
	}
	return (newline);
}

t_vector2	get_char_pos(t_readline_data *data, t_char *c)
{
	char		*build;
	t_vector2	size;
	int			prompt_len;
	int			line_len;
	t_vector2	v;

	build = build_result(*data, c);
	size = get_terminal_size(data, 0);
	prompt_len = (ft_strlen_utf8(last_newline((char *)data->prompt))
			* data->display_prompt) + data->offset;
	line_len = ft_strlen_utf8(last_newline(build));
	if (line_len == (int)ft_strlen_utf8(build))
		line_len += prompt_len;
	free(build);
	v.x = ((line_len % size.x)) + 1;
	v.y = data->pos.y + count_low_newlines(data, c)
		+ count_hard_newlines(*data, c);
	return (v);
}
