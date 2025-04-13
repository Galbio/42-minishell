/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 08:00:35 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/13 22:48:55 by gakarbou         ###   ########.fr       */
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
	else if (!itab->backslash && (str[itab->i] == '$')
		&& (itab->cur_quote != '\''))
		itab->i += go_to_var_end(str + itab->i) - 1;
	else if (!itab->backslash && !itab->cur_quote
		&& ft_strchr("<>", str[itab->i]))
	{
		add_redirection(str, itab, cmd, dest);
		if (!str[itab->i])
			itab->i--;
	}
	else if (!itab->backslash && !itab->cur_quote && (str[itab->i] == '=')
		&& (*dest == NULL))
		handle_local_appending(str, itab, cmd);
}

t_list	*fill_argv(char *str, t_cmd_params *cmd)
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

char	**fill_return_argv(t_list *argv)
{
	char	**dest;
	int		size;
	t_list	*temp;

	if (!argv)
		return (NULL);
	size = ft_lstsize(argv);
	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = 0;
	while (argv)
	{
		dest[--size] = argv->content;
		temp = argv;
		argv = argv->next;
		free(temp);
	}
	return (dest);
}

t_cmd_params	*create_command_argv(t_cmd_params *cmd)
{
	char	*input;
	char	*temp;

	input = *(cmd->argv);
	temp = input;
	input = handle_aliases(input, cmd->imp->aliases);
	if (!input)
		input = temp;
	else
	{
		free(cmd->pipes->content);
		cmd->pipes->content = input;
	}
	cmd->argv = NULL;
	cmd->argv = fill_return_argv(fill_argv(input, cmd));
	return (cmd);
}
