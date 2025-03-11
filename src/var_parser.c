/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 03:46:01 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/11 16:33:54 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_var_commands(char *command, t_list **envp, t_main_envp *imp)
{
	t_list	*commands;
	t_list	*cur;
	char	**argv;
	int		i;

	command[ft_strlen(command) - 1] = 0;
	commands = init_pipes(command, envp, imp);
	execute_line(commands, envp, imp);
	cur = commands;
	while (cur)
	{
		argv = (char **)cur->content;
		i = -1;
		while (argv[++i])
			free(argv[i]);
		free(argv);
		cur = cur->next;
	}
	free(commands);
	return (NULL);
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

void	handle_var(char *str, t_int_tab *infos, t_list **envp, t_main_envp *imp)
{
	char	*temp;

	imp->is_bquoted++;
	infos->ptr2 = get_var_str(str + infos->i + 1);
	temp = parse_var(infos->ptr2, envp, imp);
	ft_memcpy(infos->ptr1 + infos->res, temp, ft_securelen(temp));
	infos->res += ft_securelen(temp);
	infos->i += ft_securelen(infos->ptr2) + (infos->ptr2[0] == '(');
	imp->is_bquoted--;
	free(temp);
	free(infos->ptr2);
}
