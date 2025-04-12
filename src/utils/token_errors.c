/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:03:59 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/12 15:45:16 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_error(char *str)
{
	int		i;

	if (!translate(2, "token.error.start", program_arg(NULL, NULL), 0))
		return ;
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
	translate(2, "token.error.end", NULL, 1);
	set_exit_status(258);
}
