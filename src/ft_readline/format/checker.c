/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:11:11 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 15:09:19 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static int	fc(int v)
{
	static int	format_check = 1;

	if (v == 0 || v == 1)
		format_check = v;
	return (format_check);
}

void	ft_readline_set_check_format(int v)
{
	fc(v);
}

int	ft_readline_is_format_checked(void)
{
	return (fc(2));
}

int	check_quotes(const char *build)
{
	int		i;
	char	cur_quote;
	char	back_slashed;

	if (!ft_readline_is_format_checked())
		return (1);
	i = -1;
	cur_quote = 0;
	back_slashed = 0;
	while (build[++i])
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
	}
	return (cur_quote == 0);
}

int	check_backslashes(const char *build)
{
	int	i;

	if (!ft_readline_is_format_checked())
		return (1);
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
