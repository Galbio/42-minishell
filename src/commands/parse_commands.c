/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:src/builtins/pwd.c
/*   Created: 2025/02/23 17:09:54 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/06 05:03:27 by gakarbou         ###   ########.fr       */
========
/*   Created: 2025/02/23 12:55:20 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/05 16:36:13 by gakarbou         ###   ########.fr       */
>>>>>>>> refs/heads/main:src/commands/parse_commands.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pwd(void)
{
<<<<<<<< HEAD:src/builtins/pwd.c
	char	*temp;

	temp = getcwd(NULL, 0);
	write(1, temp, ft_strlen(temp));
	free(temp);
========
	t_int_tab	itab;
	char		**argv;
	char		*dest;

	itab = init_int_tab();
	argv = create_command_argv(str, envp, imp);
	itab.ret = check_built_in(&argv[0]);
	if (itab.ret)
		dest = handle_builtins(itab.ret, argv, &envp, imp);
	else
		dest = execute_command(argv, imp);
	while (argv[++itab.i])
		free(argv[itab.i]);
	return (free(argv), dest);
>>>>>>>> refs/heads/main:src/commands/parse_commands.c
}
