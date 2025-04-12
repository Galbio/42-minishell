/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 02:07:29 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/12 16:15:08 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translations.h"

static t_language	*create_language(char *name)
{
	t_language	*language;

	language = malloc(sizeof(t_language));
	language->name = ft_remove_extension(name);
	language->file = ft_strdup(name);
	language->keys = NULL;
	language->init = 0;
	return (language);
}

t_list	*parse_languages(void)
{
	t_list	*languages;
	t_array	files;
	int		size;
	int		i;
	char	*ext;

	languages = NULL;
	files = ft_scandir(LANGS_PATH, SCANDIR_SORT_NONE, 0, 0);
	i = 0;
	size = ft_array_count(files);
	while (i < size)
	{
		ext = ft_get_extension((char *)(files[i]));
		if (ext != NULL && ft_strncmp(ext, "ini", 3) == 0)
			ft_lstadd_back(&languages,
				ft_lstnew(create_language((char *)(files[i]))));
		free(ext);
		i++;
	}
	ft_array_unset(&files, ft_array_free_entry);
	return (languages);
}
