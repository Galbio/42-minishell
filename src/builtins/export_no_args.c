/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:40:47 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/06 05:04:29 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_cor_char(char c)
{
	if (c == '"')
		write(1, "\\\"", 2);
	else if (c == '\\')
		write(1, "\\\\", 2);
	else if (c == '\n')
		write(1, "\\n", 2);
	else if (c == '\t')
		write(1, "\\t", 2);
	else if (c == '\v')
		write(1, "\\v", 2);
	else if (c == '\r')
		write(1, "\\r", 2);
	else if (c == '\f')
		write(1, "\\f", 2);
	else
		write(1, &c, 1);
}

void	export_vars(t_list *envp)
{
	char	*env;
	int		i;

	while (envp)
	{
		env = (char *)envp->content;
		ft_putstr_fd("declare -x ", 1);
		i = -1;
		while (env[++i] && env[i] != '=')
			write(1, env + i, 1);
		if (!env)
			return ;
		write(1, "=\"", 2);
		while (env[++i])
			write_cor_char(env[i]);
		write(1, "\"\n", 2);
		envp = envp->next;
	}
}
