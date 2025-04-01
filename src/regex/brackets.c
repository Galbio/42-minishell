/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 06:06:08 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/01 16:30:06 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"

static void	parse_brackets(char *pattern, t_array *allowed)
{
	int			j;
	int			i;
	int			count;
	char		*values;

	i = 1;
	while (pattern[i] != ']')
	{
		count = 2 + 1 * (pattern[i + 1] && pattern[i + 1] == '-'
				&& pattern[i + 2] && pattern[i + 2] != ']');
		values = malloc(sizeof(char) * count);
		j = 0;
		while (j < (count - 1))
		{
			if (j == 1 && pattern[i + j] == '-')
				i++;
			values[j] = pattern[i + j];
			j++;
		}
		i += j;
		values[j] = '\0';
		ft_array_push(allowed, values);
	}
}

static int	is_correct_format(char *pattern)
{
	int	i;
	int	open;
	int	close;

	i = 0;
	open = 0;
	close = 0;
	while (pattern[i])
	{
		if (!open && pattern[i] == '[')
			open = 1;
		else if (pattern[i] == ']')
		{
			if (close)
				return (0);
			close = 1;
		}
		i++;
	}
	return (open && close);
}

int	brackets_match(char c, char *pattern)
{
	t_array	allowed;
	int		i;
	int		in;
	char	*value;

	if (!pattern)
		return (0);
	if (!is_correct_format(pattern))
		return (0);
	allowed = ft_array();
	parse_brackets(pattern, &allowed);
	i = 0;
	in = 0;
	while (i < ft_array_count(allowed))
	{
		value = (char *)allowed[i];
		if (!value[1])
		{
			if (c == value[0])
			{
				in = 1;
				break ;
			}
		}
		else if (c >= ft_min(value[0], value[1])
			&& c <= ft_max(value[0], value[1]))
		{
			in = 1;
			break ;
		}
		i++;
	}
	ft_array_unset(&allowed, ft_array_free_entry);
	return (in);
}

int	is_bracket(char *text, int index)
{
	int	n;

	if (text[index] != '[' && text[index] != ']')
		return (0);
	n = 0;
	while ((index - n) > 0 && text[index - n - 1] == '\\')
		n++;
	if (n % 2 == 1)
		return (0);
	return (1);
}

char	*find_brackets(char *text)
{
	int	i;

	if (!is_bracket(text, 0))
		return (NULL);
	i = 1;
	while (text[i] && !ft_iswhitespace(text[i]) && (text[i] == '[' || !is_bracket(text, i)))
		i++;
	if (text[i] != ']')
		return (NULL);
	return (ft_substr(text, 0, i + 1));
}

char	*find_brackets_from_end(char *text, int index)
{
	int	i;

	if (!is_bracket(text, index))
		return (NULL);
	
	i = index - 1;
	while (i > 0 && (!ft_iswhitespace(text[i]) && (!is_bracket(text, i) || (text[i - 1] != ']' && is_bracket(text, i - 1)))))
		i--;
	if (i == -1 || !is_bracket(text, i))
		return (NULL);
	return ft_substr(text, i, index - i + 1);
}

int	have_brackets(char *text)
{
	char	*brackets;

	brackets = find_brackets(text);
	if (!brackets)
		return (0);
	free(brackets);
	return (1);
}

int	have_brackets_from_end(char *text, int index)
{
	char	*brackets;

	brackets = find_brackets_from_end(text, index);
	if (!brackets)
		return (0);
	free(brackets);
	return (1);
}
