/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:14:37 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/06 08:04:19 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	handle_n(char *str, char *nl)
{
	int		i;

	if (!str[0] || (str[0] != '-'))
		return (0);
	i = 0;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	*nl = 0;
	return (1);
}

void	ms_echo(t_command *cmd)
{
	char	*str;
	char	nl;
	int		i;

	i = 0;
	nl = 1;
	str = ft_strdup("");
	while (cmd->argv[++i])
		if (!handle_n(cmd->argv[i], &nl))
			break ;
	i--;
	while (cmd->argv[++i])
	{
		write(1, cmd->argv[i], ft_strlen(cmd->argv[i]));
		if (cmd->argv[i + 1])
			write(1, " ", 1);
	}
	if (nl)
		write(1, "\n", 1);
}
