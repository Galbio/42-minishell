/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:14:27 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/12 22:18:41 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define RESET_COLOR "\033[0m"
#define DARK_GREEN_COLOR "\033[38;2;0;167;74m"
#define GREEN_COLOR "\033[38;2;0;200;89m"
#define TURQUOISE_COLOR "\033[38;2;0;200;188m"

static void	define_variables(t_main_envp *imp, char **user, char **cwd)
{
	*user = imp->user;
	if (!(*user))
		*user = "unknown";
	*cwd = imp->cwd;
	if (!(*cwd))
		*cwd = ft_strdup(".");
	else if (imp->home)
	{
		if (ft_strncmp(*cwd, imp->home, ft_strlen(imp->home)) == 0)
			*cwd = ft_strreplace_part(*cwd, 0, ft_strlen(imp->home), "~");
		else
			*cwd = ft_strdup(*cwd);
	}
	else
		*cwd = ft_strdup(*cwd);
}

static void	init_lenghts(int *ulen, int v1, int *clen, int v2)
{
	*ulen = v1;
	*clen = v2;
}

static char	*free_and_return(void *freeable, char *returned)
{
	free(freeable);
	return (returned);
}

char	*get_prompt(t_main_envp *imp)
{
	char	*user;
	char	*cwd;
	char	*res;
	int		ulen;
	int		clen;

	define_variables(imp, &user, &cwd);
	init_lenghts(&ulen, ft_strlen(user), &clen, ft_strlen(cwd));
	res = malloc(sizeof(char) * (ulen + clen + 11 + 3 * 16 + 17 + 4 * 2));
	if (!res)
		return (ft_strdup("better than bash $>"));
	ft_strlcpy(res, GREEN_COLOR, 17);
	ft_strlcpy(res + 16, "42-ms", 6);
	ft_strlcpy(res + 21, RESET_COLOR, 5);
	res[25] = '#';
	ft_strlcpy(res + 26, TURQUOISE_COLOR, 18);
	ft_strlcpy(res + 43, user, ulen + 1);
	ft_strlcpy(res + 43 + ulen, RESET_COLOR, 5);
	res[47 + ulen] = ':';
	ft_strlcpy(res + 48 + ulen, DARK_GREEN_COLOR, 17);
	ft_strlcpy(res + 64 + ulen, cwd, clen + 1);
	ft_strlcpy(res + 64 + ulen + clen, RESET_COLOR, 5);
	ft_strlcpy(res + 68 + ulen + clen, " $> \033[0m", 9);
	res[68 + ulen + clen + 8] = '\0';
	return (free_and_return(cwd, res));
}
