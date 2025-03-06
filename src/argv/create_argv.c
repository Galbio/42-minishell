/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 08:00:35 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/06 08:07:28 by gakarbou         ###   ########.fr       */
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
	t_int_tab	itab;

	itab = init_int_tab();
	while (str[0][++itab.i])
	{
		if ((str[0][itab.i] == 32) && !itab.cur_quote)
			break ;
		if (!check_special_char(str[0][itab.i], &itab.backslash,
			&itab.cur_quote))
			continue ;
		if ((itab.cur_quote != '\'') && str[0][itab.i] == '$')
		{
			itab.ptr1 = get_var_str(str[0] + itab.i + 1);
			itab.ptr2 = parse_var(itab.ptr1, envp, imp);
			itab.res += ft_securelen(itab.ptr2);
			itab.i += ft_securelen(itab.ptr1);
			(free(itab.ptr1), free(itab.ptr2));
		}
		else
			itab.res++;
	}
	return (itab.res);
}

static char	*parsed_quoted_substr(char **str, t_list **envp, t_main_envp *imp)
{
	t_int_tab	itab;

	itab = init_int_tab();
	itab.ptr1 = malloc(sizeof(char)
			* (get_parsed_substr_len(str, envp, imp) + 1));
	if (!itab.ptr1)
		return (NULL);
	while (str[0][++itab.i])
	{
		if ((str[0][itab.i] == 32) && !itab.cur_quote)
			break ;
		if (!check_special_char(str[0][itab.i], &itab.backslash,
			&itab.cur_quote))
			continue ;
		if ((itab.cur_quote != '\'') && str[0][itab.i] == '$')
			handle_var(str[0], &itab, envp, imp);
		else
			itab.ptr1[itab.res++] = str[0][itab.i];
	}
	itab.ptr1[itab.res] = 0;
	(*str) += itab.i + 1;
	return (itab.ptr1);
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
