/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:58:34 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/14 01:06:46 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_path_errors(char *path, int check_dir)
{
	int	res;

	res = ft_canaccess(path);
	if (check_dir && ft_isfile(path))
		return (display_error("minishell: cd: ", path,
				": Not a directory\n", 1));
	if (res == 0)
		return (display_error("minishell: cd: ", path,
				": Permission denied\n", 2));
	else
		return (display_error("minishell: cd: ", path,
				": No such file or directory\n", 3));
	return (0);
}

int	env_errors(char *path)
{
	if (ft_isdir(path) || (ft_isfile(path) && access(path, X_OK) != 0))
		return (display_error("env: ‘", path,
				"’: Permission denied\n", 1));
	else
		return (display_error("env: ‘", path,
				"’: No such file or directory\n", 1));
}
