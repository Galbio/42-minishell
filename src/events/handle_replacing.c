/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_replacing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:58:48 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/12 22:29:52 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_nth_command(int key)
{
	char	*dest;

	if (key == 0)
	{
		set_exit_status(257);
		write(2, "minishell: !0: event not found\n", 31);
		return (NULL);
	}
	dest = get_history_value(key);
	if (dest)
		return (dest);
	set_exit_status(257);
	write(2, "minishell: !", 12);
	ft_putnbr_fd(key, 2);
	write(2, ": event not found\n", 18);
	return (NULL);
}

static char	*match_history_start(char *str)
{
	t_array	history;
	int		word_len;
	int		history_size;
	int		i;

	word_len = 0;
	while (str[word_len] && !ft_strchr(" \t\n", str[word_len]))
		word_len++;
	history = get_history();
	history_size = ft_array_count(history);
	i = -1;
	while (++i < history_size)
	{
		if (!ft_strncmp(str, history[i], word_len))
			return (ft_strdup(history[i]));
	}
	write(2, "minishell: !", 12);
	write(2, str, word_len);
	write(2, ": event not found\n", 18);
	set_exit_status(258);
	return (NULL);
}

int	handle_events(char *start, char **src,
		long actual_pos, int *replaced)
{
	char	*value;
	void	*temp;
	int		len;

	if (start[1] == '!')
		value = get_nth_command(-1);
	else if (start[1] == '#')
		value = ft_substr(*src, 0, actual_pos);
	else if (is_only_nb(start + 1 + (start[1] == '-')))
		value = get_history_x(ft_atoi(start + 1));
	else
		value = match_history_start(start + 1);
	if (!value)
		return (1);
	len = 1;
	while (!ft_strchr(" #\t\n", start[len]))
		len++;
	if (start[len] == '#')
		len++;
	temp = *src;
	*src = ft_strreplace_part(*src, actual_pos, len, value);
	free(temp);
	free(value);
	*replaced = 1;
	return (0);
}
