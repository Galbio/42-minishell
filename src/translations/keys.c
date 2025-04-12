/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:20:14 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/12 13:21:45 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translations.h"

static t_key	*new_key(char *key, char *content)
{
	t_key	*new;

	new = malloc(sizeof(t_key));
	new->key = key;
	new->content = content;
	new->next = NULL;
	return (new);
}

static void	add_key(char *value, t_language *language)
{
	int		i;
	char	*key;
	char	*content;
	t_key	*cur;

	i = 0;
	while (value[i] != '=')
		i++;
	key = ft_substr(value, 0, i);
	content = ft_substr(value, i + 1, ft_strlen(value) - i - 1);
	if (language->keys == NULL)
		language->keys = new_key(key, content);
	else
	{
		cur = language->keys;
		while (cur->next)
			cur = cur->next;
		cur->next = new_key(key, content);
	}
}

void	read_lang_file(t_language **language)
{
	char	*joined;
	char	*contents;
	int		fd;
	char	**splited;
	int		i;

	joined = ft_pathjoin("./langs/", (*language)->file);
	fd = open(joined, O_RDONLY);
	if (fd == -1)
		return ;
	contents = ft_get_contents(fd);
	splited = ft_split(contents, '\n');
	i = 0;
	while (splited[i])
	{
		if (ft_strchr(splited[i], '='))
			add_key(splited[i], *language);
		free(splited[i]);
		i++;
	}
	free(joined);
	free(contents);
	free(splited);
}
