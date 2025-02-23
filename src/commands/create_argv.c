/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 08:00:35 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/23 09:50:44 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_command_argc(char *str)
{
	int		res;
	int		i;
	char	cur_quote;
	char	back_slashed;

	cur_quote = 0;
	back_slashed = 0;
	res = 0;
	i = -1;
	while (str[++i])
	{
		if ((str[i] == 32) && !cur_quote)
			res++;
		check_special_char(str[i], &back_slashed, &cur_quote);
	}
	return (res + 1);
}

int	get_parsed_substr(char **str)
{
	int		i;
	int		size;
	char	cur_quote;
	char	back_slashed;

	i = -1;
	size = 0;
	cur_quote = 0;
	back_slashed = 0;
	while (str[0][++i])
	{
		if ((str[0][i] == 32) && !cur_quote)
			break ;
		check_special_char(str[0][i], &back_slashed, &cur_quote);
	}
	return (i);
}

char	*parsed_quoted_substr(char **str)
{
	int		i;
	int		size;
	char	*dest;

	size = get_parsed_substr(str);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (++i < size)
		dest[i] = str[0][i];
	dest[i] = 0;
	(*str) += i + 1;
	return (dest);
}

char	**create_command_argv(char *str, t_list *envp, t_main_envp *imp)
{
	char	**dest;
	int		i;
	int		size;

	size = get_command_argc(str);
	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = 0;
	i = -1;
	while (++i < size)
		dest[i] = parse_quotes(parsed_quoted_substr(&str), envp, imp);
	return (dest);
}
