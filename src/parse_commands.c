/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:55:20 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/23 15:51:52 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_commands(char *str, t_list *envp, t_main_envp *imp)
{
	t_int_tab	tabe;
	char		*commande;
	char		*dest;

	tabe = init_int_tab();
	/*
	while (str[++tabe.i])
	{
		if ((str[tabe.i] == ';') && !tabe.cur_quote)
		{
			tabe.ret++;
			while ((str[tabe.i] == 32) || (str[tabe.i] == ';'))
			{
				if (str[tabe.i] == ';')
					write(2, "minishell: syntax error near", 28);
				if (str[tabe.i] == ';')
					write(2, "unexpected token `;'\n", 20);
				tabe.i++;
			}
		}
		check_special_char(str[tabe.i], &tabe.backslash, &tabe.cur_quote);
	}
	*/
	commande = parse_quotes(str, envp, imp);
	tabe.res = check_built_in(&commande);
	if (tabe.res)
		return (free(commande), ft_strdup("later"));
	dest = execute_command(commande, envp, imp);
	return (free(commande), dest);
}
