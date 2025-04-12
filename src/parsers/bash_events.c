/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:46:45 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/12 15:05:44 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_history_x(int nb)
{
	t_array	history;
	int		len;

	if (nb == 0)
	{
		set_exit_status(257);
		write(2, "minishell: !0: event not found\n", 31);
		return (NULL);
	}
	history = get_history();
	len = ft_array_count(history);
	if ((nb > 0) && (nb < len))
		return (ft_strdup(history[len - nb]));
	else if ((nb < 0) && (-nb < len))
		return (ft_strdup(history[-nb - 1]));
	set_exit_status(257);
	write(2, "minishell: !", 12);
	ft_putnbr_fd(nb, 2);
	write(2, ": event not found\n", 19);
	return (NULL);
}

static int	handle_events(char *start, char **src, long actual_pos)
{
	char	*value;

	if (start[1] == '(')
	{
		write(2, "minishell: !: event not found\n", 30);
		set_exit_status(257);
		return (1);
	}
	if (start[1] == '!')
		value = get_history_x(-1);
	else if (start[1] == '#')
		value = ft_substr(*src, 0, actual_pos);
	else if ((start[1] == '-') || ft_isdigit(start[1]))
		value = get_history_x(ft_atoi(start + 1));
	if (!value)
		return (1);
	*src = ft_strreplace_part(*src, actual_pos, 2, value);
	return (0);
}

/*char	*replace_event_subcmd(char *str, t_int_tab *tab, t_main_envp *imp)
{
}*/

char	*replace_events(char *str, t_main_envp *imp)
{
	t_int_tab	itab;

	itab = init_int_tab();
	imp->actual_pos = 0;
	while (str[++itab.i])
	{
		itab.backslash = itab.i && (str[itab.i - 1] == '\\') && !itab.backslash;
		check_special_char(str, &itab);
		if (!itab.cur_quote && (str[itab.i] == '\n'))
			break ;
		if (itab.cur_quote == '\'')
			continue ;
		/*if (!itab.backslash && (str[itab.i] == '$')
			&& (str[itab.i + 1] == '('))
		{
			imp->actual_pos += itab.i + 2;
			str = replace_events_subcmd(get_subcmd(str + itab.i + 1), &itab, imp);
			imp->actual_pos -= itab.i + 2;
			itab.i += go_to_var_end(str + itab.i) - 1;
		}*/
		if (!itab.backslash && (str[itab.i] == '!') && !ft_strchr(" \t=", str[itab.i + 1]))
		{
			imp->actual_pos += itab.i;
			if (handle_events(str + itab.i, &str, imp->actual_pos))
				break ;
			imp->actual_pos -= itab.i;
		}
	}
	return (str);
}
