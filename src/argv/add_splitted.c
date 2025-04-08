/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_splitted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:17:51 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/08 22:21:32 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_matched(t_list *matches)
{
	char	*dest;
	int		len;
	int		i;
	t_list	*cur;

	cur = matches;
	len = 0;
	while (cur)
	{
		len += ft_strlen(cur->content);
		cur = cur->next;
		if (cur)
			len++;
	}
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (matches)
	{
		len = ft_strlen(matches->content);
		ft_memcpy(dest + i, matches->content, len); 
		i += len;
		matches = matches->next;
		if (matches)
			dest[i++] = ' ';
	}
	dest[i] = 0;
	return (dest);
}

static void	replace_wildcard(char **src, char **str)
{
	t_research	*ret;
	char		*joined;
	void		*temp;
	int			sep;
	int			diff;

	ret = parse_research(*str);
	if (!ret)
		return ;
	sep = 0;
	while (str[0][sep] && !ft_strchr(" \n\t", str[0][sep]))
		sep++;
	joined = join_matched(ret->matches);
	temp = joined;
	joined = ft_strreplace_part(*str, 0, sep, joined);
	free(temp);
	diff = (*str - *src);
	temp = ft_substr(*src, 0, diff);
	free(*src);
	*src = ft_strjoin(temp, joined);
	free(temp);
	free(joined);
	*str = *src + diff;
}

static int	get_splitted_size(char **src, char *str)
{
	int		res;
	int		i;
	char	is_sep;

	res = 0;
	i = -1;
	is_sep = 1;
	while (str[++i])
	{
		if (is_sep && (str[i] == '\\') && ft_strchr(" \n\t*[?", str[i + 1]))
			is_sep = 0;
		else if (!is_sep || !ft_iswhitespace(str[i]))
		{
			if (is_sep && ft_strchr("[?*", str[i]))
				replace_wildcard(src, &str);
			res++;
			if ((str[i] == '\\') && (str[i + 1] == '\\'))
				i++;
			is_sep = 1;
		}
		else
			break ;
	}
	return (res);
}

char	*make_splitted_str(char **str, int *i, char is_sep)
{
	char	*dest;
	int		ret;

	dest = malloc(sizeof(char) * (get_splitted_size(str, str[0] + *i) + 1));
	if (!dest)
		return (NULL);
	ret = 0;
	while (str[0][*i])
	{
		if (is_sep && (str[0][*i] == '\\'))
			is_sep = 0;
		else if (!is_sep || !ft_iswhitespace(str[0][*i]))
		{
			dest[ret++] = str[0][*i];
			is_sep = 1;
		}
		else
			break ;
		(*i)++;
	}
	dest[ret] = 0;
	return (dest);
}

void	add_splitted_to_add(char *str, t_list **dest)
{
	int		i;

	if (!str[0])
		ft_lstadd_front(dest, ft_lstnew(ft_strdup("")));
	i = 0;
	while (str[i])
	{
		while (ft_iswhitespace(str[i]))
			i++;
		if (str[i])
			ft_lstadd_front(dest, ft_lstnew(make_splitted_str(&str, &i, 1)));
		while (ft_iswhitespace(str[i]))
			i++;
	}
	free(str);
}
