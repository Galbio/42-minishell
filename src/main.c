/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:20:18 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/23 07:54:03 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int			i;
	t_main_envp	imp;
	char		*temp;
	t_list		*env;

	(void)argc;
	(void)envp;
	(void)argv;
	env = parse_envp(envp, &imp);
	temp = ft_readline("$> ");
	if (!clean_readed(&temp))
		return (9);
	parse_var(temp, env, &imp);
	ft_lstclear(&env, free);
	free(temp);
	i = -1;
	while (imp.path[++i])
		free(imp.path[i]);
	free(imp.path);
	free(imp.home);
	free(imp.cwd);
	return (2);
}
