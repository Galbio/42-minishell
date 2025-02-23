/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:20:18 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/23 11:00:59 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int			i;
	t_main_envp	imp;
	char		*temp;
	char		*str;
	t_list		*env;

	(void)argc;
	(void)envp;
	(void)argv;
	env = parse_envp(envp, &imp);
	temp = ft_readline("$> ");
	if (!clean_readed(&temp))
		return (9);
	str = parse_quotes(temp, env, &imp);
	printf("%s\n", str);
	ft_lstclear(&env, free);
	free(str);
	i = -1;
	while (imp.path[++i])
		free(imp.path[i]);
	free(imp.path);
	free(imp.home);
	free(imp.cwd);
	return (2);
}
