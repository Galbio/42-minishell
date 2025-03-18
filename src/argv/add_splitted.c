/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_splitted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:17:51 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/18 19:18:24 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_splitted_size(char *str)
{
	int		res;
	int		i;
	char	is_sep;

	res = 0;
	i = -1;
	is_sep = 1;
	while (str[++i])
	{
		if ((str[i] == '\\') && ft_iswhitespace(str[i + 1]))
			is_sep = 0;
		else if (!is_sep || !ft_iswhitespace(str[i]))
		{
			res++;
			is_sep = 1;
		}
		else
			break ;
	}
	return (res);
}

static char	*make_splitted_str(char *str, int *i)
{
	char	*dest;
	int		ret;
	char	is_sep;

	dest = malloc(sizeof(char) + get_splitted_size(str + *i));
	is_sep = 1;
	(*i)--;
	ret = 0;
	while (str[++(*i)])
	{
		if ((str[*i] == '\\') && ft_iswhitespace(str[*i + 1]))
			is_sep = 0;
		else if (!is_sep || !ft_iswhitespace(str[*i]))
		{
			dest[ret++] = str[*i];
			is_sep = 1;
		}
		else
			break ;
	}
	dest[ret] = 0;
	return (dest);
}

void	add_splitted_to_add(char *str, t_list **dest)
{
	int		i;

	i = 0;
	while (str[i])
	{
		while (ft_iswhitespace(str[i]))
			i++;
		if (str[i])
			ft_lstadd_front(dest, ft_lstnew(make_splitted_str(str, &i)));
		while (ft_iswhitespace(str[i]))
			i++;
	}
	free(str);
}
