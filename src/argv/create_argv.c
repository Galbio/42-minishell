/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 08:00:35 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/26 19:15:38 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_argv_filling(char *str, t_cmd_params *cmd, t_list **dest,
		t_int_tab *itab)
{
	itab->backslash = itab->i && (str[itab->i - 1] == '\\') && !itab->backslash;
	if (check_special_char(str, itab))
		return ;
	if (!itab->cur_quote && !itab->backslash
		&& ft_strchr(" \n\t", str[itab->i]))
		add_to_argv(dest, str, itab, cmd);
	if (!itab->backslash && (str[itab->i] == '$')
		&& (itab->cur_quote != '\''))
		itab->i += go_to_var_end(str + itab->i) - 1;
	if (!itab->backslash && !itab->cur_quote && ft_strchr("<>", str[itab->i]))
	{
		add_redirection(str, itab, cmd, dest);
		if (!str[itab->i])
			itab->i--;
	}
}

static t_list	*fill_argv(char *str, t_cmd_params *cmd)
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

static void	fill_return_argv(t_cmd_params *cmd, t_list *argv)
{
	char	**dest;
	int		size;
	t_list	*temp;

	size = ft_lstsize(argv);
	if (!size)
		size = 1;
	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
	{
		cmd->argv = NULL;
		return ;
	}
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
	cmd->argv = dest;
}

t_cmd_params	*create_command_argv(t_cmd_params *cmd)
{
	t_list	*argv;
	char	*temp;

	temp = *(cmd->argv);
	cmd->argv = NULL;
	argv = fill_argv(temp, cmd);
	fill_return_argv(cmd, argv);
	return (cmd);
}
