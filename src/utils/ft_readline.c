/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:23:28 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/23 04:09:46 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	open_quote(char *stashed)
{
	int	i;
	int	v;

	i = 0;
	v = 0;
	while (stashed[i])
	{
		if (stashed[i] == v)
			v = 0;
		else if (ft_is_quote(stashed[i]) && v == 0)
			v = stashed[i];
		i++;
	}
	return (v);
}

char	*ft_readline(const char *prompt)
{
	char	*line;
	char	*res;
	char	*tmp;

	write(1, prompt, ft_strlen(prompt));
	res = malloc(sizeof(char));
	res[0] = '\0';
	while (1)
	{
		line = get_next_line(0);
		tmp = ft_strjoin(res, line);
		free(line);
		free(res);
		res = tmp;
		if (open_quote(res) == 0)
		{
			res[ft_strlen(res) - 1] = '\0';
			break ;
		}
	}
	tmp = ft_strdup(res);
	free(res);
	res = tmp;
	return (res);
}
