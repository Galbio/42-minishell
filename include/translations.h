/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translations.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:07:24 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 22:42:33 by lroussel         ###   ########.fr       */
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
	t_key	*keys;
}	t_language;

typedef struct s_translations
{
	t_language	*language;
	t_array		languages;
}	t_translations;

t_translations	*get_translations(void);
void			init_translations(void);

char			*translate(char *key, t_array *args);
void			display_translation(int fd, char *key, t_array *args,
					int new_line);

int				set_language(char *name);

void			free_translations(void);

char			*apply_args(char *value, t_array *args);

void			add_translation_arg(t_array *args, char *value);
int				is_translation_arg(char *value);
t_array			base_command_args(char *program_name, char *command_name);
t_array			simple_arg(char *v);

t_array			parse_languages(void);

#endif
