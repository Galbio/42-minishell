/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:40:47 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 11:40:45 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_addr(char **ptr1, char **ptr2)
{
	char	*temp;

	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

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

static void	sort_envp(char **envp)
{
	int		i;
	int		j;

	i = -1;
	while (envp[++i])
	{
		j = i;
		while (envp[++j])
			if (ft_strncmp(envp[i], envp[j], -1) > 0)
				swap_addr(&envp[i], &envp[j]);
	}
}

void	export_vars(t_list *envp)
{
	char	**envp_cpy;
	int		i;
	int		j;

	envp_cpy = create_envp_cpy(&envp, NULL);
	sort_envp(envp_cpy);
	i = -1;
	while (envp_cpy[++i])
	{
		write(1, "declare -x ", 11);
		j = -1;
		while (envp_cpy[i][++j] && (envp_cpy[i][j] != '='))
			write(1, envp_cpy[i] + j, 1);
		if (!envp_cpy[i])
			return ;
		write(1, "=\"", 2);
		while (envp_cpy[i][++j])
			write_cor_char(envp_cpy[i][j]);
		write(1, "\"\n", 2);
		free(envp_cpy[i]);
	}
	free(envp_cpy);
}
