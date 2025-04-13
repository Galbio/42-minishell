/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:03:59 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/11 22:41:14 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_error(char *str)
{
	int		i;

	write(2, "minishell: syntax error near unexpected token `", 47);
	if (!str[0])
		write(2, "newline", 7);
	else if (ft_strchr("()", str[0]))
		write(2, str, 1);
	else if (ft_strchr("<>", str[0]))
	{
		i = -1;
		while ((++i < 3) && (str[i] == str[0]))
		{
			write(2, str, 1);
			if ((str[0] == '>') && i)
				break ;
		}
	}
	else
		write(2, str, 1 + (str[0] == str[1]));
	write(2, "'\n", 2);
	set_exit_status(258);
}
