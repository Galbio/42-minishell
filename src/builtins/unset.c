/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:34:13 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/23 20:11:20 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_from_envp(t_list **envp, t_main_envp *imp, int i)
{
	t_list	*temp;
	t_list	*head;

	(void)imp;
	head = *envp;
	if (!i)
	{
		(free((*envp)->content), temp = *envp);
		(*envp = (*envp)->next, free(envp));
		return ;
	}
	while (--i > 0)
		head = head->next;
	temp = head->next;
	head->next = head->next->next;
	(free(temp->content), free(temp));
	return ;
}

void	unset_var(char *name, t_list **envp, t_main_envp *imp)
{
	int		len;
	int		i;
	char	*env;
	t_list	*head;

	len = ft_strlen(name);
	i = -1;
	head = *envp;
	while (head)
	{
		i++;
		env = (char *)head->content;
		if (!ft_strncmp(name, env, len) && (env[len] == '='))
		{
			remove_from_envp(envp, imp, i);
			return ;
		}
		head = head->next;
	}
}

void	*ft_unset(char *name, t_list **envp, t_main_envp *imp)
{
	char	*trimmed_name;
	int		i;

	if (!name[5])
		return (NULL);
	name += 6;
	i = 0;
	if ((name[i] != '_') && (!ft_isalnum(name[i])))
		return (NULL);
	while (name[++i])
	{
		if (name[i] == 32)
			break ;
		if ((name[i] != '_') && (!ft_isalnum(name[i])))
			return (NULL);
	}
	trimmed_name = ft_substr(name, 0, i);
	unset_var(name, envp, imp);
	free(name - 6);
	return (free(trimmed_name), NULL);
}
