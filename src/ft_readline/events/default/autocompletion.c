/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:23:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/13 13:49:34 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static void	autocomplete(t_readline_data *data, char *value, char *res)
{
	int		i;
	int		len;
	char	*slash;

	slash = ft_strrchr(value, '/');
	if (slash)
		i = ft_strlen(slash + 1);
	else
		i = ft_strlen(value);
	len = ft_strlen(res);
	if (res[len - 1] == '/' && res[len - 2] == '/')
		res[len-- - 1] = '\0';
	if (i <= len)
	{
		while (res[i])
		{
			process_default_key(data, res + i);
			i++;
		}
	}
	if (res[len - 1] != '/')
		process_default_key(data, " ");
	on_write(data);
	free(value);
	free(res);
}

void	tab_key(t_readline_data *data)
{
	char	*value;
	char	*res;

	if (data->first == NULL)
		return ;
	if (data->tab_pressed)
	{
		display_autocompletion(data);
		if (data->display_prompt)
			write(2, data->prompt, ft_strlen(data->prompt));
		data->pos.y = data->cursor.y - count_low_newlines(data, data->current)
			- count_hard_newlines(*data, data->current);
		on_write(data);
		return ;
	}
	value = get_argument_before(data->current);
	if (!value)
		value = ft_strdup("");
	res = research_autocompletion(data, value);
	if (res)
	{
		autocomplete(data, value, res);
		return ;
	}
	free(value);
}
