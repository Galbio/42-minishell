/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:10:32 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/09 13:10:20 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

t_vector2	get_char_pos(t_readline_data *data, t_readline_char *c)
{
	char		*build;
	t_vector2	size;
	int			prompt_len;
	int			line_len;
	t_vector2	v;

	build = list_to_string(*data, c);
	size = get_terminal_size(data, 0);
	prompt_len = (ft_strlen_utf8(ft_getlast_newline((char *)data->prompt))
			* data->display_prompt) + data->offset;
	line_len = ft_strlen_utf8(ft_getlast_newline(build));
	if (line_len == (int)ft_strlen_utf8(build))
		line_len += prompt_len;
	free(build);
	v.x = ((line_len % size.x)) + 1;
	v.y = data->pos.y + count_low_newlines(data, c)
		+ count_hard_newlines(*data, c);
	return (v);
}
