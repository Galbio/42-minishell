/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:03:59 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/14 09:14:13 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_error(char *str, int i)
{
	int		j;

	write(2, "minishell: syntax error near unexpected token `", 47);
	if (str[0] == '|')
		write(2, "|", 1);
	else if (!str[i] || ft_strncmp(str, "<>", 3) == 0)
		write(2, "newline", 7);
	else if (ft_strchr("()", str[i]))
		write(2, str, 1);
	else if (ft_strchr("<>", str[i]))
	{
		j = -1;
		while ((++j < 3) && (str[i + j] == str[i]))
		{
			write(2, str + i, 1);
			if ((str[i] == '>') && j)
				break ;
		}
	}
	else
		write(2, str + i, 1 + (str[i] == str[i + 1]));
	write(2, "'\n", 2);
	if (!isatty(STDIN_FILENO))
	{
		write(2, " `", 2);
		write(2, str, ft_strlen(str));
		write(2, "'\n", 2);
	}
	set_exit_status(258);
}
