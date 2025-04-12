/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lang.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:18:13 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/12 14:48:07 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	list_languages(void)
{
	t_list		*languages;
	t_language	*language;

	languages = get_translations()->languages;
	while (languages)
	{
		language = (t_language *)(languages->content);
		write(1, language->name, ft_strlen(language->name));
		if (languages->next)
			write(1, ", ", 2);
		languages = languages->next;
	}
}

static int	check_args(char **argv, t_list *args)
{
	if (!argv[1])
	{
		translate(2, "command.lang.usage", args, 1);
		return (0);
	}
	if (argv[2])
	{
		translate(2, "command.lang.usage", args, 1);
		return (0);
	}
	return (1);
}

int	ms_lang(t_cmd_params *cmd)
{
	char	*value;
	t_list	*args;

	args = program_arg("lang", NULL);
	if (!check_args(cmd->argv, args))
		return (0);
	value = cmd->argv[1];
	if (ft_strncmp(value, "list", ft_strlen(value) + 1) == 0)
	{
		if (translate(1, "command.lang.list", args, 0))
		{
			list_languages();
			write(2, "\n", 1);
		}
		return (0);
	}
	if (!set_language(value))
	{
		translate(2, "command.lang.invalid", args, 1);
		return (0);
	}
	ft_lstadd_back(&args, ft_lstnew(value));
	translate(1, "command.lang.success", args, 1);
	return (0);
}
