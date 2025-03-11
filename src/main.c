/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:20:18 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/05 17:26:50 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int			i;
	t_main_envp	imp;
	t_list		*env;

	(void)argc;
	(void)argv;
	env = parse_envp(envp, &imp);
	launch(env, &imp);
	ft_lstclear(&env, free);
	i = -1;
	while (imp.path[++i])
		free(imp.path[i]);
	free(imp.path);
	free(imp.home);
	return (2);
}
