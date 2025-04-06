/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:39:01 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 21:44:01 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translations.h"

int	set_language(char *name)
{
	t_translations	*translations;
	t_array			languages;
	int				size;
	int				i;
	t_language		*language;

	translations = get_translations();
	languages = translations->languages;
	size = ft_array_count(languages);
	i = 0;
	while (i < size)
	{
		language = (t_language *)(languages[i]);
		if (ft_strncmp(name, language->name, ft_strlen(name) + 1) == 0)
		{
			translations->language = language;
			return (1);
		}
		i++;
	}
	return (0);
}

char	*translate(char *key, t_array *args)
{
	t_key	*keys;

	keys = get_translations()->language->keys;
	while (keys)
	{
		if (ft_strncmp(keys->key, key, ft_strlen(key)) == 0)
			return (apply_args(keys->content, args));
		keys = keys->next;
	}
	return (ft_strdup(key));
}

void	display_translation(int fd, char *key, t_array *args, int new_line)
{
	char	*message;

	message = translate(key, args);
	if (args)
		ft_array_unset(args, ft_array_nothing_entry);
	write(fd, message, ft_strlen(message));
	free(message);
	if (new_line)
		write(fd, "\n", 1);
}

static t_language	*get_default_language(t_translations *translations)
{
	t_array	languages;
	int		i;
	int		size;

	languages = translations->languages;
	i = 0;
	size = ft_array_count(languages);
	if (size == 0)
		return (NULL);
	while (i < size)
	{
		if (ft_strncmp(((t_language *)languages[i])->name, "en", 3) == 0)
			return ((t_language *)languages[i]);
		i++;
	}
	return ((t_language *)languages[0]);
}

t_translations	*get_translations(void)
{
	static t_translations	*translations = NULL;

	if (!translations)
	{
		translations = malloc(sizeof(t_translations));
		translations->languages = parse_languages();
		translations->language = get_default_language(translations);
	}
	return (translations);
}
