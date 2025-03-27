/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:20:18 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 03:46:45 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*res;
	if (!argv[1])
		res = process_wildcards("/home/sunset/cursus/minishell/", "Make*e");
	else
		res = process_wildcards("/home/sunset/cursus/minishell/", argv[1]);
	t_list	*cur = res;
	while (cur)
	{
		printf("%s\n", (char *)cur->content);
		t_list	*tmp = cur->next;
		free(cur->content);
		free(cur);
		cur = tmp;
	}
	return 0;
	t_main_envp	imp;
	t_list		*env;

	(void)argc;
	(void)argv;
	env = parse_envp(envp, &imp);
	launch(env, &imp);
	free_envp(&env, &imp);
	return (2);
}
