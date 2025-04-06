/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:17:36 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 21:47:43 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translations.h"

static int	get_final_size(char *value, t_array *args)
{
	int	size;
	int	i;
	int	array_size;
	int	count;

	size = 0;
	i = -1;
	count = 0;
	array_size = ft_array_count(*args);
	while (value[++i])
	{
		if (count < array_size && is_translation_arg(value + i))
		{
			i += 2;
			count++;
			continue ;
		}
		size++;
	}
	if (array_size < count)
		count = array_size;
	i = -1;
	while (++i < count)
		size += ft_strlen((char *)((*args)[i]));
	return (size);
}

static void	paste_arg(char *value, int *index, char *arg)
{
	int	len;

	len = ft_strlen(arg);
	ft_memcpy(value + *index, arg, len);
	*index += len;
}

static int	create_res(char *value, t_array *args, char **res)
{
	if (!args)
		return (0);
	*res = malloc(sizeof(char) * (get_final_size(value, args) + 1));
	return (res != NULL);
}

char	*apply_args(char *value, t_array *args)
{
	char	*res;
	int		i;
	int		j;
	int		k;
	int		size;

	if (!create_res(value, args, &res))
		return (ft_strdup(value));
	i = 0;
	j = 0;
	k = 0;
	size = ft_array_count(*args);
	while (value[i])
	{
		if (k < size && is_translation_arg(value + i))
		{
			paste_arg(res, &j, (char *)(*args)[k]);
			i += 3;
			k++;
			continue ;
		}
		res[j++] = value[i++];
	}
	res[j] = '\0';
	return (res);
}
