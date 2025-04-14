/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:05:06 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/14 06:20:19 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "regex.h"

static int	over_u64(char *str, long long int *res)
{
	long long int	nb;
	int				i;
	int				sign;

	nb = 0;
	i = 0;
	sign = 1;
	if (ft_strchr("+-", str[i]))
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
	{
		if ((nb >= 922337203685477580) && (str[i] > ('8' - (sign > 0))))
			return (1);
		nb = (nb * 10) + (str[i++] - '0');
	}
	if (str[i])
		return (1);
	*res = nb * sign;
	return (0);
}

static char	check_exit_error(char **argv, long long int *code)
{
	int				i;

	i = 0;
	while (ft_strchr(" \t\n", argv[1][i]))
		i++;
	if (!ft_strchr("+-", argv[1][i]) && !ft_isdigit(argv[1][i]))
		return (display_error("minishell: exit: ", argv[1],
				": numeric argument required\n", 1));
	if (ft_strchr("+-", argv[1][i]) && !ft_isdigit(argv[1][i + 1]))
		return (display_error("minishell: exit: ", argv[1],
				": numeric argument required\n", 1));
	if (over_u64(argv[1] + i, code))
		return (display_error("minishell: exit: ", argv[1],
				": numeric argument required\n", 1));
	if (argv[2])
		return (display_error("minishell: exit: too many arguments\n",
				"", "", 0));
	return (2);
}

static char	parse_exit(t_cmd_params *cmd)
{
	int				res;
	long long int	code;

	code = 0;
	res = check_exit_error(cmd->argv, &code);
	if (!res)
		return (0);
	if (res == 2)
	{
		free_cmd(cmd, 1);
		free_envp(cmd->envp, cmd->imp);
		if (!get_depth(0))
		{
			free_readline();
			free_regex_items();
		}
		free(cmd);
		exit(code);
	}
	return (1);
}

int	ms_exit(t_cmd_params *cmd)
{
	int		res;
	char	av1;

	res = get_exit_status();
	av1 = cmd->argv[1] != NULL;
	if (!get_depth(0) && isatty(STDIN_FILENO))
		write(STDERR_FILENO, "exit\n", 5);
	if (!av1 || (parse_exit(cmd) == 1))
	{
		free_cmd(cmd, 1);
		free_envp(cmd->envp, cmd->imp);
		if (!get_depth(0))
		{
			free_readline();
			free_regex_items();
		}
		free(cmd);
		if (!av1)
			exit(res);
		exit(2);
	}
	return (1);
}
