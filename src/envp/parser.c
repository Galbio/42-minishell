/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:57:32 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/10 15:16:40 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_path_count(char *str)
{
	int		res;
	int		i;

	res = 0;
	i = -1;
	while (str[++i])
		if ((str[i] == ':') && (str[i - 1] != '\\'))
			res++;
	return (res + 1);
}

char	*malloc_pathname(char **str)
{
	char	*dest;
	int		size;
	int		i;

	i = -1;
	size = 0;
	while (str[0][++size])
		if ((str[0][size] == ':') && (str[0][size - 1] != '\\'))
			break ;
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = 0;
	i = -1;
	while (++i < size)
		dest[i] = str[0][i];
	*str += size + 1;
	return (dest);
}

char	**parse_path(char *str)
{
	char	**dest;
	int		size;

	size = get_path_count(str);
	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = 0;
	while (--size >= 0)
		dest[size] = malloc_pathname(&str);
	return (dest);
}

void	handle_important(char *str, t_main_envp *imp)
{
	static char	important[4] = {0, 0, 0, 0};

	if (!important[0] && !ft_strncmp("SHLVL=", str, 6))
	{
		important[0]++;
		imp->shell_level = ft_atoi(str + 6);
	}
	else if (!important[2] && !ft_strncmp("HOME=", str, 5))
	{
		important[2]++;
		imp->home = ft_strdup(str + 5);
	}
	else if (!important[3] && !ft_strncmp("PATH=", str, 5))
	{
		important[3]++;
		imp->path = parse_path(str + 5);
	}
	else if (!imp->pwd && !important[4] && !ft_strncmp("PWD=", str, 4) && str[4] != '\0')
	{
		important[4]++;
		imp->pwd = ft_strdup(str + 5);
	}
}

t_list	*parse_envp(char **envp, t_main_envp *imp)
{
	t_list	*dest;
	void	*temp;
	int		i;

	if (!envp || !envp[0])
		return (NULL);
	dest = NULL;
	i = -1;
	imp->pwd = getcwd(NULL, 0);
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "SHLVL=", 6))
		{
			temp = ft_itoa(ft_atoi(envp[i] + 6) + 1);
			ft_lstadd_back(&dest, ft_lstnew(ft_strjoin("SHLVL=", temp)));
			free(temp);
		}
		else
			ft_lstadd_back(&dest, ft_lstnew(ft_strdup(envp[i])));
		handle_important(envp[i], imp);
	}
	imp->aliases = NULL;
	return (dest);
}
