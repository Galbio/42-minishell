/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:33:44 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/26 13:34:33 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		else if ((build[i] == '\'' || build[i] == '\"') && !back_slashed)
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

int	check_backslashs(const char *build)
{
	int	i;

	i = 0;
	while (build[i])
	{
		if (build[i] == '\\')
		{
			i++;
			while (build[i] == '\n')
				i++;
			if (!build[i])
				return (0);
		}
		i++;
	}
	return (1);
}
