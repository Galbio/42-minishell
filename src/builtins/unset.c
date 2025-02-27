/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:34:13 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/27 15:23:49 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_env(int i, t_list **envp)
{
	t_list	*cur;
	t_list	*temp;

	cur = *envp;
	if (!i)
	{
		temp = cur->next;
		ft_lstdelone(cur, free);
		*envp = temp;
		return ;
	}
	while (i != 1)
	{
		i--;
		cur = cur->next;
	}
	temp = cur->next->next;
	ft_lstdelone(cur->next, free);
	cur->next = temp;
}

void	unset_var(char *name, t_list **envp, t_main_envp *imp)
{
	t_list	*cur;
	char	*env;
	int		i;
	int		len;

	(void)imp;
	i = 0;
	len = ft_strlen(name);
	cur = *envp;
	while (cur)
	{
		env = (char *)cur->content;
		if ((!ft_strncmp(env, name, len)) && (env[len] == '='))
		{
			delete_env(i, envp);
			return ;
		}
		cur = cur->next;
		i++;
	}
}

void	*ft_unset(char **argv, t_list **envp, t_main_envp *imp)
{
	int		i;

	if (!argv[1])
		return (NULL);
	i = 0;
	while (argv[++i])
		unset_var(argv[i], envp, imp);
	return (NULL);
}
