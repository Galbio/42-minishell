/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:02:30 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/12 14:31:40 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translations.h"

t_key	*get_translation_key(char *key)
{
	t_translations	*translations;
	t_key			*keys;
	int				len;

	translations = get_translations();
	if (!translations->active)
		return (NULL);
	keys = ((t_language *)translations->active->content)->keys;
	len = ft_strlen(key);
	while (keys)
	{
		if (ft_strncmp(keys->key, key, len + 1) == 0)
			return (keys);
		keys = keys->next;
	}
	return (NULL);
}

static int	check_translation_key(t_key **translation_key, char *key, int fd,
	t_list *args)
{
	*translation_key = get_translation_key(key);
	if (!(*translation_key))
	{
		write(fd, key, ft_strlen(key));
		write(fd, "\n", 1);
		ft_lstclear(&args, ft_nothing);
		return (0);
	}
	return (1);
}

static void	free_and_next(t_list **value)
{
	t_list	*tmp;

	tmp = (*value)->next;
	free(*value);
	*value = tmp;
}

int	translate(int fd, char *key, t_list *args, int new_line)
{
	int		i;
	int		j;
	t_key	*translation_key;

	if (!check_translation_key(&translation_key, key, fd, args))
		return (0);
	i = 0;
	j = -1;
	while (++j < (int)ft_strlen(translation_key->content))
	{
		if (args && is_translation_argument(translation_key->content + j))
		{
			write(fd, translation_key->content + i, j - i);
			write(fd, (char *)args->content, ft_strlen((char *)args->content));
			free_and_next(&args);
			j += 2;
			i = j + 1;
		}
	}
	if (i < j)
		write(fd, translation_key->content + i, j - i);
	if (new_line)
		write(fd, "\n", 1);
	ft_lstclear(&args, ft_nothing);
	return (1);
}
