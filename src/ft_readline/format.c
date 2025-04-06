/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:11:11 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/25 19:18:13 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	check_quotes(const char *build)
{
	int		i;
	char	cur_quote;
	char	back_slashed;

	i = 0;
	cur_quote = 0;
	back_slashed = 0;
	while (build[i])
	{
		if (build[i] == '\\' && !back_slashed)
			back_slashed = 1;
		else if (build[i] == '\''
			|| ((build[i] == '`' || build[i] == '\"') && !back_slashed))
		{
			if (cur_quote == build[i])
				cur_quote = 0;
			else if (cur_quote == 0)
				cur_quote = build[i];
		}
		else
			back_slashed = 0;
		i++;
	}
	return (cur_quote == 0);
}

int	check_backslashes(const char *build)
{
	int	i;

	i = 0;
	while (build[i])
	{
		if (build[i] == '\\')
		{
			i++;
			if (!build[i] || (build[i] == '\n' && !build[i + 1]))
				return (0);
		}
		i++;
	}
	return (1);
}

static int	new_size(char *build, int old_size)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < old_size)
	{
		if ((i + 3 <= old_size) && (ft_strncmp(build + i, "\\\n", 2) == 0))
			i += 2;
		len++;
		i++;
	}
	return (len);
}

char	*clean_backslashes(char *build)
{
	char	*res;
	int		i;
	int		j;
	int		old_size;

	old_size = ft_strlen(build);
	res = malloc((new_size(build, old_size) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < old_size)
	{
		if ((i + 3 <= old_size) && (ft_strncmp(build + i, "\\\n", 2) == 0))
			i += 2;
		res[j] = build[i];
		j++;
		i++;
	}
	res[j] = '\0';
	free(build);
	return (res);
}
