/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 02:11:58 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/12 16:19:57 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translations.h"

static void	init_language(t_language *language)
{
	read_lang_file(&language);
	language->init = 1;
}

int	set_language(char *name)
{
	t_translations	*translations;
	t_list			*languages;
	t_language		*language;
	int				len;

	translations = get_translations();
	languages = translations->languages;
	len = ft_strlen(name);
	while (languages)
	{
		language = (t_language *)(languages->content);
		if (ft_strncmp(name, language->name, len + 1) == 0)
		{
			if (!language->init)
				init_language(language);
			translations->active = languages;
			return (1);
		}
		languages = languages->next;
	}
	return (0);
}

t_translations	*get_translations(void)
{
	static t_translations	*translations = NULL;

	if (!translations)
	{
		translations = malloc(sizeof(t_translations));
		translations->languages = parse_languages();
		translations->active = NULL;
		set_language("en");
	}
	return (translations);
}

static void	free_language(void *value)
{
	t_language	*language;
	t_key		*temp;

	language = (t_language *)value;
	free(language->name);
	free(language->file);
	while (language->keys)
	{
		temp = language->keys->next;
		free(language->keys->key);
		free(language->keys->content);
		free(language->keys);
		language->keys = temp;
	}
	free(language);
}

void	free_translations(void)
{
	t_translations	*translations;

	translations = get_translations();
	ft_lstclear(&translations->languages, free_language);
	free(translations);
}
