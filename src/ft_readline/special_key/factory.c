/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:31:17 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/26 18:58:25 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	on_overwrite(char *sequence)
{
	int	i;

	write(2, "Key with id '", 13);
	ft_putstr_fd(sequence, 2);
	write(2, "[", 1);
	i = 0;
	while (sequence[i])
	{
		ft_putnbr_fd(sequence[i], 2);
		if (i < 3 && sequence[i + 1])
			write(2, ";", 1);
		i++;
	}
	write(2, "]", 1);
	write(2, "' already exist.\n", 17);
}

void	register_special_key(char *sequence, void (*callback)(t_readline *))
{
	t_readline_core	*main;
	int				count;

	if (get_by_sequence(sequence) != NULL)
		on_overwrite(sequence);
	main = get_readline_core();
	count = get_special_keys_count();
	main->special_keys = ft_realloc(
			main->special_keys,
			sizeof(t_special_key *) * (count + 1),
			sizeof(t_special_key *) * (count + 2)
			);
	main->special_keys[count] = malloc(sizeof(t_special_key));
	main->special_keys[count]->sequence = sequence;
	main->special_keys[count]->callback = callback;
	main->special_keys[count + 1] = NULL;
}

t_special_key	*get_by_sequence(char *sequence)
{
	t_special_key	**special_keys;
	int				i;

	special_keys = get_readline_core()->special_keys;
	i = 0;
	while (special_keys[i])
	{
		if (ft_strncmp(sequence,
				special_keys[i]->sequence, ft_max(ft_strlen(sequence),
					ft_strlen(special_keys[i]->sequence))) == 0)
			return (special_keys[i]);
		i++;
	}
	return (NULL);
}

t_special_key	**get_special_keys(void)
{
	return (get_readline_core()->special_keys);
}

int	get_special_keys_count(void)
{
	t_special_key	**special_keys;
	int				i;

	special_keys = get_readline_core()->special_keys;
	i = 0;
	while (special_keys[i])
		i++;
	return (i);
}
