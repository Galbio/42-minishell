/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 21:44:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 21:48:55 by lroussel         ###   ########.fr       */
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

static void	read_lang_file(char *name, t_language *language)
{
	char	*joined;
	char	*contents;
	int		fd;
	char	**splited;
	int		i;

	joined = ft_pathjoin("./langs/", name);
	fd = open(joined, O_RDONLY);
	if (fd == -1)
		return ;
	contents = ft_get_contents(fd);
	splited = ft_split(contents, '\n');
	i = 0;
	while (splited[i])
	{
		if (ft_strchr(splited[i], '='))
			add_key(splited[i], language);
		free(splited[i]);
		i++;
	}
	free(joined);
	free(contents);
	free(splited);
}

static t_language	*create_language(char *name)
{
	t_language	*language;

	language = malloc(sizeof(t_language));
	language->name = ft_remove_extension(name);
	language->keys = NULL;
	read_lang_file(name, language);
	return (language);
}

t_array	parse_languages(void)
{
	t_array	languages;
	t_array	files;
	int		size;
	int		i;
	char	*ext;

	languages = ft_array();
	files = ft_scandir("./langs/", SCANDIR_SORT_NONE, 0, 0);
	i = 0;
	size = ft_array_count(files);
	while (i < size)
	{
		ext = ft_get_extension((char *)(files[i]));
		if (ext != NULL && ft_strncmp(ext, "ini", 3) == 0)
			ft_array_push(&languages, create_language((char *)(files[i])));
		free(ext);
		i++;
	}
	ft_array_unset(&files, ft_array_free_entry);
	return (languages);
}
