/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:57:20 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/18 01:49:35 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_parsed_size(char *str, t_list **cmd_outputs, t_cmd_params cmd)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (str[++itab.i])
	{
		if (!check_special_char(str[itab.i], &itab.backslash, &itab.cur_quote))
			continue ;
		if ((str[itab.i] == '$') && (itab.cur_quote != '\'') && !itab.backslash)
			handle_var(str, &itab, cmd_outputs, cmd);
		else
			itab.res++;
	}
	return (itab.res);
}

void	add_var_to_dest(char *dest, char *str, t_int_tab *itab,
		t_list **cmd_outputs)
{
	char		*to_add;
	int			len;
	t_list		*temp;

	to_add = ((char *)(*cmd_outputs)->content);
	len = ft_strlen(to_add);
	ft_memcpy(dest + itab->res, to_add, len);
	temp = *cmd_outputs;
	*cmd_outputs = temp->next;
	free(temp->content);
	free(temp);
	itab->res += len;
	itab->i += go_to_var_end(str + itab->i);
	itab->i--;
}

static char	*parse_quotes(char *str, t_cmd_params cmd)
{
	char		*dest;
	t_list		*cmd_outputs;
	t_int_tab	itab;

	itab = init_int_tab();
	cmd_outputs = NULL;
	itab.ret = get_parsed_size(str, &cmd_outputs, cmd);
	dest = malloc(sizeof(char) * (itab.ret + 1));
	if (!dest)
		return (NULL);
	dest[itab.ret] = 0;
	while (str[++itab.i])
	{
		if (!check_special_char(str[itab.i], &itab.backslash, &itab.cur_quote))
			continue ;
		if ((str[itab.i] == '$') && (itab.cur_quote != '\'') && !itab.backslash)
			add_var_to_dest(dest, str, &itab, &cmd_outputs);
		else
			dest[itab.res++] = str[itab.i];
	}
	free(str);
	return (dest);
}

void	add_to_argv(t_list **dest, char *str, t_int_tab *itab,
		t_cmd_params cmd)
{
	char	*to_add;
	char	**splitted;
	int		i;

	if (str[itab->ret])
	{
		to_add = parse_quotes(ft_substr(str, itab->ret,
					itab->i - itab->ret), cmd);
		if (itab->cur_quote)
			ft_lstadd_front(dest, ft_lstnew(to_add));
		else
		{
			splitted = ft_split(to_add, ' ');
			i = -1;
			while (splitted[++i])
				ft_lstadd_front(dest, ft_lstnew(splitted[i]));
			free(splitted);
			free(to_add);
		}
		itab->ret = itab->i + 1;
	}
}
