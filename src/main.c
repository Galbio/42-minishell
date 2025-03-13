/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:20:18 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/13 01:06:44 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_all(t_list *env, t_main_envp *imp)
{
	int		i;

	ft_lstclear(&env, free);
	i = -1;
	while (imp->path[++i])
		free(imp->path[i]);
	i = -1;
	while (imp->envp_cpy[++i])
		free(imp->envp_cpy[i]);
	free(imp->envp_cpy);
	free(imp->path);
	free(imp->home);
}

int	main(int argc, char **argv, char **envp)
{
	t_main_envp	imp;
	t_list		*env;

	(void)argc;
	(void)argv;
	env = parse_envp(envp, &imp);
	launch(env, &imp);
	free_all(env, &imp);
	return (2);
}
