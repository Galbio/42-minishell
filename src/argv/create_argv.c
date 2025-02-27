/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 08:00:35 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/27 21:18:04 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_command_argc(char *str)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (str[++itab.i])
	{
		if ((str[itab.i] == 32) && !itab.cur_quote)
			itab.res++;
		if ((str[itab.i] == '$') && (str[itab.i + 1] == '('))
			while (str[itab.i] != ')')
				itab.i++;
		check_special_char(str[itab.i], &itab.backslash, &itab.cur_quote);
	}
	return (itab.res + 1);
}

static int	get_parsed_substr_len(char **str, t_list **envp, t_main_envp *imp)
{
	t_int_tab	tabe;

	tabe = init_int_tab();
	while (str[0][++tabe.i])
	{
		if ((str[0][tabe.i] == 32) && !tabe.cur_quote)
			break ;
		if (!check_special_char(str[0][tabe.i], &tabe.backslash,
			&tabe.cur_quote))
			continue ;
		if ((tabe.cur_quote != '\'') && str[0][tabe.i] == '$')
		{
			tabe.ptr1 = get_var_str(str[0] + tabe.i + 1);
			tabe.ptr2 = parse_var(tabe.ptr1, envp, imp);
			tabe.res += ft_securelen(tabe.ptr2);
			tabe.i += ft_securelen(tabe.ptr1);
			(free(tabe.ptr1), free(tabe.ptr2));
		}
		else
			tabe.res++;
	}
	return (tabe.res);
}

static char	*parsed_quoted_substr(char **str, t_list **envp, t_main_envp *imp)
{
	t_int_tab	tabe;

	tabe = init_int_tab();
	tabe.ret = get_parsed_substr_len(str, envp, imp);
	tabe.ptr1 = malloc(sizeof(char) * (tabe.ret + 1));
	if (!tabe.ptr1)
		return (NULL);
	while (str[0][++tabe.i])
	{
		if ((str[0][tabe.i] == 32) && !tabe.cur_quote)
			break ;
		if (!check_special_char(str[0][tabe.i], &tabe.backslash,
			&tabe.cur_quote))
			continue ;
		if ((tabe.cur_quote != '\'') && str[0][tabe.i] == '$')
		{
			imp->is_bquoted++;
			handle_var(str[0], &tabe, envp, imp);
			imp->is_bquoted--;
		}
		else
			tabe.ptr1[tabe.res++] = str[0][tabe.i];
	}
	tabe.ptr1[tabe.res] = 0;
	(*str) += tabe.i + 1;
	return (tabe.ptr1);
}

char	**create_command_argv(char *str, t_list **envp, t_main_envp *imp)
{
	char	**dest;
	int		i;
	int		size;

	size = get_command_argc(str);
	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = 0;
	i = -1;
	while (++i < size)
		dest[i] = parsed_quoted_substr(&str, envp, imp);
	return (dest);
}
