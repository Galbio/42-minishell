/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:27:20 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/27 14:48:30 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*get_pwd(char *home)
{
	char	*cur_pwd;
	char	*dest;
	int		home_len;

	cur_pwd = getcwd(NULL, 0);
	if (!home)
	{
		if (!cur_pwd)
			return (ft_strdup("/"));
		return (cur_pwd);
	}
	home_len = ft_strlen(home);
	if (!ft_strncmp(home, cur_pwd, home_len))
	{
		dest = ft_strjoin("~", cur_pwd + home_len);
		free(cur_pwd);
		return (dest);
	}
	return (cur_pwd);
}

char	*get_prompt(t_main_envp *imp)
{
	char	*dest;
	char	*base;
	int		len;

	base = get_pwd(imp->home);
	len = ft_strlen(base);
	dest = malloc(sizeof(char) * (len + 17 + !base[1]));
	ft_memcpy(dest, "abcdef/", 7);//ft_memcpy(dest, "\e[0;32m", 7);
	ft_memcpy(dest + 7, base, len);
	if (!base[1])
		ft_memcpy(dest + 7 + len, "/$ ", 3);
	else
		ft_memcpy(dest + 7 + len, "$ ", 2);
	ft_memcpy(dest  + 9 + len + !base[1], "lololo ", 7);//"\e[0;37m", 7);
	dest[len + 17 + !base[1]] = 0;
	free(base);
	return (dest);
}
