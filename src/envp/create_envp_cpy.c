/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envp_cpy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 06:49:41 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/09 20:24:57 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_envp_size(t_list *envp)
{
	int		res;

	res = 0;
	while (envp)
	{
		if (((char *)(envp->content))[0] != '\\')
			res++;
		envp = envp->next;
	}
	return (res);
}

static void	fill_dest(char *saw_shlvl, t_main_envp *imp, char *str, char **dest)
{
	char	*level;

	if ((*saw_shlvl == 0) && !ft_strncmp("SHLVL=", str, 6))
	{
		*saw_shlvl = 1;
		level = ft_itoa(imp->exit_status + 1);
		*dest = ft_strjoin("SHLVL=", level);
		free(level);
	}
	else if (str[0] != '\\')
		*dest = ft_strdup(str);
}

char	**create_envp_cpy(t_list **envp, t_main_envp *imp)
{
	char	**dest;
	t_list	*cur;
	int		i;
	char	saw_shlvl;

	dest = malloc(sizeof(char *) * (get_envp_size(*envp) + 1));
	if (!dest)
		return (NULL);
	saw_shlvl = 0;
	if (!imp || imp->shell_level == 0)
	{
		if (imp)
			ft_lstadd_back(envp, ft_lstnew(ft_strdup("SHLVL=0")));
		saw_shlvl = 1;
	}
	i = 0;
	cur = *envp;
	while (cur)
	{
		fill_dest(&saw_shlvl, imp,
			(char *)cur->content, dest + i++);
		cur = cur->next;
	}
	dest[i] = NULL;
	return (dest);
}
