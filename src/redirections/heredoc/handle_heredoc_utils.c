/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 02:02:39 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/11 22:39:39 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_line(char *content, char *line)
{
	char	*dest;
	int		len;
	int		line_len;

	if (!content)
	{
		dest = ft_strjoin(line, "\n");
		free(line);
		return (dest);
	}
	len = ft_strlen(content);
	line_len = ft_strlen(line);
	dest = malloc(sizeof(char) * (len + line_len + 2));
	if (!dest)
		return (NULL);
	ft_memcpy(dest, content, len);
	ft_memcpy(dest + len, line, line_len);
	dest[len + line_len] = '\n';
	dest[len + line_len + 1] = 0;
	free(content);
	free(line);
	return (dest);
}

char	*wait_value(t_list **heredocs, char *value, char ignore_tab)
{
	char	*content;
	char	*line;
	int		len;
	int		i;

	content = NULL;
	len = ft_strlen(value);
	while (1)
	{
		i = 0;
		if (!(*heredocs)->next)
			(*heredocs)->next = ft_lstnew(ft_readline("> "));
		if (!(*heredocs)->next->content)
			return (content);
		*heredocs = (*heredocs)->next;
		line = ft_strdup((char *)(*heredocs)->content);
		while (ignore_tab && line[i] && (line[i] == '\t'))
			i++;
		if (!ft_strncmp(value, line, len + 1))
		{
			free(line);
			return (content);
		}
		content = add_line(content, line);
	}
}

char	advance_itab(char *str, t_int_tab *itab, char *ignore_tab, char save)
{
	int		count;
	int		i;
	int		limit;

	count = 1;
	limit = 3 - (save == '>');
	while (str[itab->i + count] == save)
		count++;
	if ((count == 2) && (str[itab->i + 2] == '-'))
		(*ignore_tab)++;
	i = itab->i + count + *ignore_tab;
	while (str[i] && ft_strchr(" \t", str[i]))
		i++;
	if (ft_strchr("<>()|&;", str[i]) || (count > limit))
	{
		if (count > limit)
			i = itab->i + limit;
		token_error(str + i);
		return (1);
	}
	itab->i = i;
	return ((save == '>') || (count != 2));
}

void	add_heredoc_history(t_list *cur, t_list **end)
{
	char	*cmd;
	void	*temp;

	if (cur == *end)
	{
		add_to_history(cur->content);
		*end = cur->next;
		free(cur->content);
		free(cur);
		return ;
	}
	cmd = NULL;
	while (cur != *end)
	{
		cmd = add_line(cmd, cur->content);
		temp = cur;
		cur = cur->next;
		free(temp);
	}
	cmd = add_line(cmd, cur->content);
	add_to_history(cmd);
	free(cmd);
	*end = cur->next;
	free(cur);
}

void	free_heredocs(t_list *cur)
{
	int		count;
	t_list	*temp;

	count = 0;
	while (cur)
	{
		if ((count % 3) == 2)
			free(cur->content);
		temp = cur;
		cur = cur->next;
		free(temp);
		count++;
	}
}
