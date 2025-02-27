/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:21:54 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/27 20:49:50 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	get_parsed_len(char *str, t_list *envp, t_main_envp *imp)
{
	t_int_tab	infos;

	infos.i = -1;
	infos.res = 0;
	infos.cur_quote = 0;
	infos.backslash = 0;
	while (str[++infos.i])
	{
		if (!check_special_char(str[infos.i], &infos.backslash,
				&infos.cur_quote))
			continue ;
		if ((infos.cur_quote != '\'') && str[infos.i] == '$')
		{
			infos.ptr1 = get_var_str(str + infos.i + 1);
			infos.ptr2 = parse_var(infos.ptr1, envp, imp);
			infos.res += ft_securelen(infos.ptr2);
			infos.i += ft_securelen(infos.ptr1);
			(free(infos.ptr1), free(infos.ptr2));
		}
		else
			infos.res++;
	}
	return (infos.res);
}

char	*parse_quotes(char *str, t_list *envp, t_main_envp *imp)
{
	t_int_tab	infos;

	infos.ptr1 = malloc(sizeof(char) * (1 + get_parsed_len(str, envp, imp)));
	if (!infos.ptr1)
		return (NULL);
	infos.i = -1;
	infos.res = 0;
	infos.cur_quote = 0;
	infos.backslash = 0;
	while (str[++infos.i])
	{
		if (!check_special_char(str[infos.i], &infos.backslash,
				&infos.cur_quote))
			continue ;
		if ((infos.cur_quote != '\'') && (str[infos.i] == '$')
			&& (!infos.backslash))
			handle_var(str, &infos, envp, imp);
		else
			infos.ptr1[infos.res++] = str[infos.i];
	}
	infos.ptr1[infos.res] = 0;
	return (infos.ptr1);
}
