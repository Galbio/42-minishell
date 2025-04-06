/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:45:46 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 19:58:19 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translations.h"

static void	free_languages(int key, void *value)
{
	t_language	*language;
	t_key		*temp;

	(void)key;
	language = (t_language *)value;
	free(language->name);
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
	ft_array_unset(&translations->languages, free_languages);
	free(translations);
}
