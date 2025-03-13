/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 03:46:01 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/13 16:33:35 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_commands(t_list *cur)
{
	t_list	*temp;

	return ;
	while (cur)
	{
		free(cur->content);
		temp = cur;
		cur = cur->next;
		free(temp);
	}
}

static char	*handle_var_commands(char *command, t_list **envp, t_main_envp *imp)
{
	t_list	*commands;
	int		old_redir;
	int		pipes[2];
	char	*dest;

	if (pipe(pipes) < 0)
		return (NULL);
	imp->is_bquoted++;
	old_redir = imp->output_fd;
	imp->output_fd = pipes[1];
	command[ft_strlen(command) - 1] = 0;
	commands = split_semicolon(command);
	execute_line(commands, envp, imp);
	imp->output_fd = old_redir;
	close(pipes[1]);
	imp->is_bquoted--;
	free_commands(commands);
	dest = ft_get_contents(pipes[0]);
	close(pipes[0]);
	return (clean_whitespaces(dest));
}

char	*parse_var(char *var_name, t_list **envp, t_main_envp *imp)
{
	t_list	*cur;
	char	*cur_env;
	int		len;

	if (var_name[0] == '(')
		return (handle_var_commands(var_name + 1, envp, imp));
	len = ft_strlen(var_name);
	cur = *envp;
	while (cur)
	{
		cur_env = (char *)cur->content;
		if ((cur_env[len] == '=') && (!ft_strncmp(cur_env, var_name, len)))
			return (ft_strdup(cur_env + len + 1));
		cur = cur->next;
	}
	return (NULL);
}

char	*get_var_str(char *str)
{
	int		i;
	char	pare;
	int		pare_count;

	i = -1;
	pare = (str[0] == '(');
	pare_count = 0;
	while (str[++i])
	{
		if ((str[i] != '_') && (!ft_isalnum(str[i])) && (!pare))
			return (ft_substr(str, 0, i));
		else if (str[i] == '(')
			pare_count++;
		else if (str[i] == ')')
			pare_count--;
		if (pare && !pare_count)
			return (ft_substr(str, 0, i + 1));
	}
	return (ft_substr(str, 0, i + 1));
}

void	handle_var(char *str, t_int_tab *infos, t_list **output)
{
	char	*output_str;
	int		len;
	t_list	*temp;

	output_str = (char *)(*output)->content;
	len = ft_securelen(output_str);
	infos->ptr2 = get_var_str(str + infos->i + 1);
	ft_memcpy(infos->ptr1 + infos->res, output_str, len);
	infos->res += len;
	infos->i += ft_securelen(infos->ptr2);
	free(infos->ptr2);
	temp = *output;
	*output = (*output)->next;
	free(temp);
	free(output_str);
}
