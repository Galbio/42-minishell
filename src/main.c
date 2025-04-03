/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:20:18 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/03 15:55:38 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "regex.h"

int	main(int argc, char **argv, char **envp)
{
	init_regexs();
/*	t_regex_item*regex = get_regex_item_from_end(argv[2], ft_strlen(argv[2]) - 1);
	if (!regex)
		printf("(null)\n");
	else
	{
		printf("%s\n", regex->last_finded);//regex_item_match(argv[1], argv[2], regex));
	}
	return (0);
	*/
	t_list	*res;
	if (!argv[1])
		res = search_pattern("/home/sunset/cursus/minishell/", "[[[a-z]*[[[a-z]*[[[a-z]*[[[a-z]*[[[a-z]*[[[a-z]");
	else
		res = search_pattern("/home/sunset/cursus/minishell/", argv[1]);
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
