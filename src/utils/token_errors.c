/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:03:59 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/14 09:38:10 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_redirs(char *str)
{
	int		j;

	j = -1;
	while ((++j < 3) && (str[j] == str[0]))
	{
		write(2, str, 1);
		if ((str[0] == '>') && j)
			break ;
	}
}

void	token_error(char *str, int i)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	if (ft_strchr("<>", str[i]) && (str[i + 1] && ft_strchr("<>", str[i + 1]))
		&& (i > 0 && ft_strchr("<>", str[i - 1])))
		i--;
	if (str[0] == '|')
		write(2, "|", 1);
	else if (!str[i] || ft_strncmp(str, "<>", 3) == 0)
		write(2, "newline", 7);
	else if (ft_strchr("()", str[i]) && str[i] == ')')
		write(2, ")", 1);
	else if (ft_strchr("<>", str[i]))
		write_redirs(str + i);
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
