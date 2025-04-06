/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:31:17 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 14:00:40 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

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

void	register_special_key(char *sequence,
	void (*callback)(t_readline_data *))
{
	t_special_key	*new;

	if (get_by_sequence(sequence) != NULL)
		on_overwrite(sequence);
	new = malloc(sizeof(t_special_key));
	new->sequence = sequence;
	new->callback = callback;
	ft_array_push(&get_readline_core()->special_keys, new);
}

t_special_key	*get_by_sequence(char *sequence)
{
	t_array			special_keys;
	int				i;
	int				size;
	t_special_key	*element;

	special_keys = get_readline_core()->special_keys;
	i = 0;
	size = ft_array_count(special_keys);
	while (i < size)
	{
		element = (t_special_key *)(special_keys[i]);
		if (ft_strncmp(sequence, element->sequence, ft_max(ft_strlen(sequence),
					ft_strlen(element->sequence))) == 0)
			return (special_keys[i]);
		i++;
	}
	return (NULL);
}
