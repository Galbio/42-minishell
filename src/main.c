/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:20:18 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/10 00:42:07 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "regex.h"

int	main(int argc, char **argv, char **envp)
{
	t_main_envp	imp;
	t_list		*env;

	(void)argc;
	(void)argv;
	env = parse_envp(envp, &imp);
	if (!imp.pwd)
	{
		printf("shell-init: error retrieving current directory: getcwd:");
		printf("cannot access parent directories: No such file or directory\n");
	}
	launch(env, &imp);
	free_envp(&env, &imp);
	free_regex_items();
	return (2);
}
