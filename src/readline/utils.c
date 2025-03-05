/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:11:11 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/05 10:17:33 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int	count_newlines(t_char *c, t_char *actual, int *lc)
{
	int	bn_count;

	bn_count = 0;
	while (c && c != actual)
	{
		(*lc)++;
		if (c->c == '\n')
		{
			bn_count++;
			*lc = 0;
		}
		c = c->next;
	}
	return (bn_count);
}

char	get_open_quote(const char *stashed)
{
	int		i;
	char	cur_quote;
	char	back_slashed;

	i = 0;
	cur_quote = 0;
	back_slashed = 0;
	while (stashed[i])
	{
		if (stashed[i] == '\\' && !back_slashed)
			back_slashed = 1;
		else if ((stashed[i] == '\'' || stashed[i] == '\"') && !back_slashed)
		{
			if (cur_quote == stashed[i])
				cur_quote = 0;
			else if (cur_quote == 0)
				cur_quote = stashed[i];
		}
		else
			back_slashed = 0;
		i++;
	}
	return (cur_quote);
}

void	init_terminal_size(t_vector2 *size)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	size->x = w.ws_col;
	size->y = w.ws_row;
}

t_vector2	get_terminal_size(t_readline *data)
{
	struct winsize	w;
	t_vector2		size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	size.x = w.ws_col;
	size.y = w.ws_row;
	check_resize(data, size);
	return (size);
}

int	count_hard_newlines(t_readline data, int to_actual)
{
	int		i;
	int		count;
	t_char	*c;
	t_char	*to;

	i = 0;
	count = 0;
	while (data.prompt[i])
		count += (data.prompt[i++] == '\n');
	c = data.first;
	to = NULL;
	if (to_actual)
	{
		if (!data.actual)
			return (0);
		to = data.actual->next;
	}
	while (c && c != to)
	{
		count += c->c == '\n';
		c = c->next;
	}
	return (count);
}

#include <stdio.h>
#include <stdlib.h>

int compteur = 1; // Variable globale pour suivre le numéro du fichier

void save(const char *texte)
{
    char nom_fichier[20];
    snprintf(nom_fichier, sizeof(nom_fichier), "temp%d.txt", compteur);
    compteur++; // Incrémentation du compteur
    
    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    
    fprintf(fichier, "%s", texte);
    fclose(fichier);
    printf("Texte sauvegardé dans %s\n", nom_fichier);
}

