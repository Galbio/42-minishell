/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:11:56 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/14 08:41:10 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**replace_argv(char **argv, int start)
{
	char	**dest;
	int		i;

	i = start;
	while (argv[i])
		i++;
	dest = malloc(sizeof(char *) * ((i - start) + 1));
	if (!dest)
		return (argv);
	i = start - 1;
	while (argv[++i])
		dest[i - start] = argv[i];
	dest[i - start] = 0;
	i = -1;
	while (++i < start)
		free(argv[i]);
	free(argv);
	return (dest);
}

static char	check_error(t_cmd_params *cmd)
{
	int		i;

	i = 0;
	while (cmd->argv[++i])
	{
		if (!ft_strchr(cmd->argv[i], '='))
		{
			cmd->argv = replace_argv(cmd->argv, i);
			set_exit_status(execute_single_bin(cmd, 1));
			return (1);
		}
	}
	return (0);
}

static void	print_envp(t_cmd_params *cmd)
{
	t_list	*cur;
	char	*temp;
	int		i;

	cur = *(cmd->envp);
	while (cur)
	{
		temp = (char *)cur->content;
		if (temp[0] == '\\')
			continue ;
		write(1, temp, ft_securelen(temp));
		write(1, "\n", 1);
		cur = cur->next;
	}
	i = 0;
	while (cmd->argv[++i])
	{
		write(1, cmd->argv[i], ft_strlen(cmd->argv[i]));
		write(1, "\n", 1);
	}
}

int	ms_env(t_cmd_params *cmd)
{
	if (cmd->argv[1])
		if (check_error(cmd))
			return (get_exit_status());
	print_envp(cmd);
	return (0);
}
