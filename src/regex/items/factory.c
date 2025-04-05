/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:47:35 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/05 14:11:26 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

void	init_regexs(void)
{
	register_regex_item("[...]",
		square_brackets_parse,
		square_brackets_match
		);
	register_regex_item("[^...]",
		square_brackets_parse,
		square_brackets_neg_match
		);
	register_regex_item("[!...]",
		square_brackets_parse,
		square_brackets_neg_match
		);
}

t_array	*get_regex_items(void)
{
	static t_array	*items = NULL;

	if (!items)
	{
		items = malloc(sizeof(t_array));
		*items = ft_array();
	}
	return (items);
}

void	register_regex_item(char *format,
	int (*parse_callback)(char *value, t_array *array),
	int (*match_callback)(char *value, t_array parsed))
{
	t_regex_item	*item;
	int				i;

	i = 0;
	while (format[i] && format[i] != '.')
		i++;
	if (!format[i]
		|| !format[i + 1] || format[i + 1] != '.'
		|| !format[i + 2] || format[i + 2] != '.'
		|| !format[i + 3])
		return ;
	item = malloc(sizeof(t_regex_item));
	if (!item)
		return ;
	item->format = format;
	item->parse_callback = parse_callback;
	item->match_callback = match_callback;
	item->last_finded = NULL;
	ft_array_unshift(get_regex_items(), item);
}

t_array	parse_regex_item(char *value, t_regex_item *item)
{
	t_array	values;
	int		i;
	int		len;

	i = 0;
	while (item->format[i] != '.')
		i++;
	len = ft_strlen(value);
	values = ft_array();
	while (i < len && !match_end(value + i, item->format))
		i += (item->parse_callback)(value + i, &values);
	return (values);
}

int	regex_item_match(char *value, char *pattern, t_regex_item *item)
{
	t_array	parsed;
	int		res;

	parsed = parse_regex_item(pattern, item);
	res = (item->match_callback)(value, parsed);
	ft_array_unset(&parsed, ft_array_free_entry);
	return (res);
}
