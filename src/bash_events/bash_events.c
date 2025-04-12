/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:46:45 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/12 21:36:25 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_events_subcmd(char *str, int *replaced);

static void	replace_subcmd(char **src, t_int_tab *itab, int *replaced)
{
	char	*temp;
	char	*replaced_subcmd;
	int		subcmd_len;

	subcmd_len = get_subcmd_size(*src + itab->i + 1);
	replaced_subcmd = replace_events_subcmd(
			get_subcmd(*src + itab->i + 1), replaced);
	if (!replaced_subcmd)
		return ;
	temp = *src;
	*src = ft_strreplace_part(*src, itab->i + 2, subcmd_len - 2,
			replaced_subcmd);
	free(replaced_subcmd);
	free(temp);
	itab->i += subcmd_len;
}

static int	iterate(char *str, char **src, t_int_tab *itab, int *replaced)
{
	itab->backslash = itab->i && (str[itab->i - 1] == '\\') && !itab->backslash;
	check_special_char(str, itab);
	if (!itab->cur_quote && (str[itab->i] == '\n'))
		return (1);
	if (itab->cur_quote == '\'')
		return (0);
	if (!itab->backslash && (str[itab->i] == '$')
		&& (str[itab->i + 1] == '('))
		replace_subcmd(src, itab, replaced);
	else if (!itab->backslash && (str[itab->i] == '!')
		&& !ft_strchr(" \t=", str[itab->i + 1]))
		if (handle_events(str + itab->i, src, itab->i, replaced))
			return (1);
	return (0);
}

static char	*replace_events_subcmd(char *str, int *replaced)
{
	t_int_tab	itab;

	itab = init_int_tab();
	while (str[++itab.i])
		if (iterate(str, &str, &itab, replaced))
			break ;
	if (get_exit_status() > 255)
		return (NULL);
	return (str);
}

char	*replace_events(char *str)
{
	t_int_tab	itab;
	int			replaced;

	replaced = 0;
	itab = init_int_tab();
	while (str[++itab.i])
		if (iterate(str, &str, &itab, &replaced))
			break ;
	if (replaced)
		printf("%s\n", str);
	return (str);
}
