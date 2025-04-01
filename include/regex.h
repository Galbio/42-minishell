/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:13:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/28 16:13:17 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_H
# define REGEX_H

#include <stdlib.h>

#include "libft.h"
#include "stdio.h"

t_list	*process_wildcards(char *path, char *pattern);
int		brackets_match(char c, char *pattern);
char	*find_brackets(char *text);
char	*find_brackets_from_end(char *text, int index);
int		have_brackets(char *text);
int		have_brackets_from_end(char *text, int index);

//len
int		min_value_len(char *pattern);
int		max_value_len(char *pattern);

#endif
