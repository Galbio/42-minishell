/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:20:18 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/01 14:28:08 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "regex.h"

int	main(int argc, char **argv, char **envp)
{
	
	t_list	*res;
	if (!argv[1])
		res = process_wildcards("/home/sunset/cursus/minishell/", "[[[a-z]*[[[a-z]*[[[a-z]*[[[a-z]*[[[a-z]*[[[a-z]");
	else
		res = process_wildcards("/home/sunset/cursus/minishell/", argv[1]);
	if (!res)
	{
		printf("%s\n", argv[1]);
		return (0);
	}
	t_list	*cur = res;
	while (cur)
	{
		printf("%s", (char *)cur->content);
		t_list	*tmp = cur->next;
		free(cur->content);
		free(cur);
		cur = tmp;
		if (cur)
			printf(" ");
	}
	printf("\n");
	return 0;
	t_main_envp	imp;
	t_list		*env;

	(void)argc;
	(void)argv;
	env = parse_envp(envp, &imp);
	launch(env, &imp);
	free_envp(&env, &imp, 0);
	return (2);
}
