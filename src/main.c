/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:20:18 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/26 20:29:53 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_main_envp	imp;
	t_list		*env;

	(void)argc;
	(void)argv;
	env = parse_envp(envp, &imp);
	launch(env, &imp);
	free_envp(&env, &imp, 0);
	return (2);
}
