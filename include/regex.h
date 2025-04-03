/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:13:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/03 15:49:46 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_H
# define REGEX_H

#include <stdlib.h>

#include "libft.h"
#include "stdio.h"

typedef struct s_regex
{
	char	*format;
	int	(*parse_callback)(char *value, t_array *array);
	int	(*match_callback)(char *value, t_array parsed);
	char	*last_finded;
}	t_regex_item;

int	regex_match(char *text, char *pattern);

//len
int		min_value_len(char *pattern);
int		max_value_len(char *pattern);

int		square_brackets_parse(char *value, t_array *array);
int		square_brackets_match(char *value, t_array parsed);
int		square_brackets_neg_match(char *value, t_array parsed);

void		init_regex(void);
void		register_regex_item(char *format, int (*parse_callback)(char *value, t_array *array), int (*match_callback)(char *value, t_array parsed));
t_array		*get_regex_items(void);
t_regex_item		*get_regex_item(char *value);
t_regex_item		*get_regex_item_from_end(char *value, int index);
t_array		parse_regex_item(char *value, t_regex_item *item);
int		regex_item_match(char *value, char *pattern, t_regex_item *item);

int		is_start(char *value, char *format);
int		is_end(char *value, char *format);
int		is_another_end(char *text, int index);

#endif
