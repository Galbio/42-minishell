/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 08:00:35 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/19 20:43:19 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_argv_filling(char *str, t_cmd_params cmd, t_list **dest,
		t_int_tab *itab)
{
	if (check_special_char(str, itab))
		return ;
	if (!itab->cur_quote && !itab->backslash
		&& ft_strchr(" \n\t", str[itab->i]))
		add_to_argv(dest, str, itab, cmd);
	if (!itab->backslash && (str[itab->i] == '$')
		&& (itab->cur_quote != '\''))
		itab->i += go_to_var_end(str + itab->i);
	/*if (itab->backslash && !itab->cur_quote
		&& ft_strchr("$\"\\", str[itab->i]))
		itab->backslash = 0;*/
}

static t_list	*fill_argv(char *str, t_cmd_params cmd)
{
	t_list		*dest;
	t_int_tab	itab;

	dest = NULL;
	itab = init_int_tab();
	while (str[++itab.i])
		handle_argv_filling(str, cmd, &dest, &itab);
	add_to_argv(&dest, str, &itab, cmd);
	return (dest);
}

char	**create_command_argv(char *str, t_list **envp, t_main_envp *imp)
{
	t_list	*argv;
	t_list	*temp;
	char	**dest;
	int		size;

	argv = fill_argv(str, make_cmd(NULL, envp, imp));
	size = ft_lstsize(argv);
	if (!size)
		size = 1;
	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = 0;
	if (!argv)
		dest[0] = ft_strdup("");
	while (argv)
	{
		dest[--size] = argv->content;
		temp = argv;
		argv = argv->next;
		free(temp);
	}
	return (dest);
}
