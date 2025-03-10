/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:11:11 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/10 10:04:28 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

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

t_vector2	get_terminal_size(t_readline *data, int check_resize)
{
	struct winsize	w;
	t_vector2		size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	size.x = w.ws_col;
	size.y = w.ws_row;
	if (check_resize && (size.x != data->old_tsize.x || size.y != data->old_tsize.y))
		on_resize(data, size);
	return (size);
}

int	count_low_newlines(t_readline *data, t_char *to)
{
	int		i;
	int		j;
	t_vector2	size;
	int		count;
	t_char	*c;
	int		nl;

	i = 0;
	j = 0;
	size = get_terminal_size(data, 0);
	count = 0;
	nl = 0;
	while (data->prompt[i])
	{
		j++;
		if (data->prompt[i] == '\n' || (j >= size.x))
		{
			count += j / size.x;
			j = nl;
			nl &= data->prompt[i] == '\n';
		}
		i++;
	}
	if ((to && !data->actual) || (data->first && !data->actual))
		return (0);
	c = data->first;
	while (c && (to == NULL || c != to->next))
	{
		j++;
		if (c->c == '\n' || (j >= size.x))
		{
			count += j / size.x;
			j = nl;
			nl &= data->prompt[i] == '\n';
		}
		c = c->next;
	}
	return (count);
}

int	count_hard_newlines(t_readline data, t_char *to)
{
	int		i;
	int		count;
	t_char	*c;

	i = 0;
	count = 0;
	while (data.prompt[i])
		count += (data.prompt[i++] == '\n');
	c = data.first;
	if ((to && !data.actual) || (data.first && !data.actual))
		return (0);
	while (c && (to == NULL || c != to->next))
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
    snprintf(nom_fichier, sizeof(nom_fichier), "temp%d.txt",  compteur);
    compteur++; // Incrémentation du compteur
    
    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    
    fprintf(fichier, "%s", texte);
    fclose(fichier);
}

