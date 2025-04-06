/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:16:30 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 14:16:11 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_none(char *readed)
{
	int	i;
	int	v;

	i = 0;
	v = 0;
	while (readed[i])
	{
		if (readed[i] == v)
			v = 0;
		else if (ft_isquote(readed[i]) && v == 0)
			v = readed[i];
		if (v != 0 && ft_isquote(readed[i]) && readed[i] != v)
			return (0);
		if (!ft_isquote(readed[i]) && !ft_iswhitespace(readed[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	clean_size(char *readed)
{
	int	i;
	int	v;
	int	size;

	i = 0;
	v = 0;
	size = 0;
	while (readed[i])
	{
		if (readed[i] == v)
			v = 0;
		else if (ft_isquote(readed[i]) && v == 0)
			v = readed[i];
		while (v == 0 && ft_iswhitespace(readed[i])
			&& ft_iswhitespace(readed[i + 1]))
			i++;
		i++;
		size++;
	}
	if (i != 0 && ft_iswhitespace(readed[i - 1]))
		size--;
	return (size);
}

static void	fix_spaces(char *readed, char **cleaned)
{
	int	i;
	int	size;
	int	v;

	i = 0;
	size = 0;
	v = 0;
	while (readed[i])
	{
		if (readed[i] == v)
			v = 0;
		else if (ft_isquote(readed[i]) && v == 0)
			v = readed[i];
		while (v == 0 && ft_iswhitespace(readed[i])
			&& ft_iswhitespace(readed[i + 1]))
			i++;
		(*cleaned)[size] = readed[i];
		size++;
		i++;
	}
	if (i != 0 && ft_iswhitespace(readed[i - 1]))
		size--;
	(*cleaned)[size] = '\0';
}

int	clean_readed(char **readed)
{
	int		i;
	int		size;
	char	*cleaned;

	if (is_none(*readed))
		return (0);
	i = 0;
	while (ft_iswhitespace((*readed)[i]))
		i++;
	size = clean_size(*readed + i);
	cleaned = malloc(sizeof(char *) * (size + 1));
	fix_spaces(*readed + i, &cleaned);
	free(*readed);
	*readed = cleaned;
	return (1);
}
