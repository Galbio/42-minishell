/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translations.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:07:24 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/12 14:49:53 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSLATIONS_H
# define TRANSLATIONS_H

# include <stdlib.h>
# include <fcntl.h>

# include "libft.h"

typedef struct s_key
{
	char			*key;
	char			*content;
	struct s_key	*next;
}	t_key;

typedef struct s_language
{
	char	*name;
	char	*file;
	t_key	*keys;
	int		init;
}	t_language;

typedef struct s_translations
{
	t_list		*active;
	t_list		*languages;
}	t_translations;

//arguments.c
int				is_translation_argument(char *value);
t_list			*new_arg(void *value, t_list *next);
t_list			*program_arg(char *value, t_list *next);

//keys.c
void			read_lang_file(t_language **language);

//manager.c
int				set_language(char *name);
t_translations	*get_translations(void);
void			free_translations(void);

//parser.c
t_list			*parse_languages(void);

//translator.c
t_key			*get_translation_key(char *key);
int				translate(int fd, char *key, t_list *args, int new_line);

#endif
