/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:19:55 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/14 05:51:34 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_to_home(t_cmd_params *cmd)
{
	int		res;
	char	*home_val;

	res = 0;
	home_val = get_var_value("HOME", *(cmd->envp));
	if (home_val)
		res = chdir(home_val);
	else
		write(2, "minishell: cd: HOME not set\n", 28);
	if (res)
	{
		command_path_errors(cmd->argv[1], 1);
		free(home_val);
		return (1);
	}
	res = home_val == NULL;
	change_envp_pwd(cmd, getcwd(NULL, 0));
	free(home_val);
	return (res);
}

static int	cd_absolute(t_cmd_params *cmd)
{
	int		res;

	res = chdir(cmd->argv[2]);
	if (res < 0 && command_path_errors(cmd->argv[1], 1) > 0)
		return (1);
	change_envp_pwd(cmd, getcwd(NULL, 0));
	return (0);
}

static int	cd_oldpwd(t_cmd_params *cmd)
{
	char	*old_pwd;
	int		res;

	old_pwd = get_var_value("OLDPWD", *(cmd->envp));
	if (old_pwd)
	{
		res = chdir(old_pwd);
		if (res < 0 && command_path_errors(cmd->argv[1], 1) > 0)
		{
			free(old_pwd);
			return (1);
		}
		write(1, old_pwd, ft_strlen(old_pwd));
		write(1, "\n", 1);
	}
	else
		write(2, "minishell: cd: OLDPWD not set\n", 30);
	res = old_pwd != NULL;
	change_envp_pwd(cmd, getcwd(NULL, 0));
	free(old_pwd);
	return (res);
}

static int	handle_dash(t_cmd_params *cmd)
{
	if (!cmd->argv[1][1])
		return (cd_oldpwd(cmd));
	if ((cmd->argv[1][1] != '-') || (cmd->argv[1][2]))
	{
		write(2, "minishell: cd: -", 16);
		ft_putchar_fd(cmd->argv[1][1], 2);
		write(2, ": invalid option\n", 17);
		return (1);
	}
	if ((cmd->argv[1][1] == '-') && !cmd->argv[2])
		return (cd_to_home(cmd));
	return (cd_absolute(cmd));
}

int	ms_cd(t_cmd_params *cmd)
{
	int		res;

	if (!cmd->argv[1])
		return (cd_to_home(cmd));
	if (!cmd->argv[1][0])
		return (0);
	if (cmd->argv[1][0] == '-')
		return (handle_dash(cmd));
	if (cmd->argv[2])
	{
		return (display_error("minishell: cd: ", cmd->argv[1],
				": too many arguments\n", 1));
	}
	res = chdir(cmd->argv[1]);
	if (res < 0 && command_path_errors(cmd->argv[1], 1) > 0)
		return (1);
	change_envp_pwd(cmd, getcwd(NULL, 0));
	return (0);
}
