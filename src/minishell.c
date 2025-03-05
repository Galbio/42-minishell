/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:50:10 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/05 16:32:59 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(void)
{
	struct termios	raw;

	enable_raw_mode(&raw);
}

void	print_pipe_sep(char *str, t_list **envp, t_main_envp *imp)
{
	t_int_tab	itab;
	t_list		*commands;

	(void)envp;
	(void)imp;
	itab = init_int_tab();
	commands = NULL;
	while (str[++itab.i])
	{
		if ((str[itab.i] == '|') && !itab.backslash && !itab.cur_quote && (
				str[itab.i + 1] != '|'))
		{
			itab.ptr1 = ft_substr(str, itab.ret, itab.i - itab.ret);
			itab.ret = itab.i + 1;
			printf("Commande = |%s|\n", itab.ptr1);
		}
		check_special_char(str[itab.i], &itab.backslash, &itab.cur_quote);
	}
	itab.ptr1 = ft_substr(str, itab.ret, itab.i);
	itab.ret = itab.i;
	printf("Command = |%s|\n", itab.ptr1);
}

void	launch(t_list *envp, t_main_envp *imp)
{
	char	*res;
	char	*str;

	init();
	while (1)
	{
		res = ft_readline("$> ");
		if (!res)
			break ;
		if (!clean_readed(&res))
		{
			free(res);
			continue ;
		}
		print_pipe_sep(res, &envp, imp);
		str = execute_command(res, &envp, imp);
		free(res);
		if (str)
			(printf("%s", str), free(str));
	}
	printf("\n");
}
