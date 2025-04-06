/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lang.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:18:13 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 22:24:49 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	list_languages(void)
{
	t_array		languages;
	int			size;
	int			i;
	t_language	*language;

	languages = get_translations()->languages;
	size = ft_array_count(languages);
	i = 0;
	while (i < size)
	{
		language = (t_language *)(languages[i]);
		write(1, language->name, ft_strlen(language->name));
		i++;
		if (i != size)
			write(1, ", ", 2);
	}
}

static int	check_args(char **argv, t_array *args)
{
	if (!argv[1])
	{
		display_translation(2, "command.lang.usage", args, 1);
		return (0);
	}
	if (argv[2])
	{
		display_translation(2, "command.toomanyargs", args, 1);
		return (0);
	}
	return (1);
}

int	ms_lang(t_cmd_params *cmd)
{
	char	*value;
	t_array	args;

	args = base_command_args("minishell", "lang");
	if (!check_args(cmd->argv, &args))
		return (0);
	value = cmd->argv[1];
	if (ft_strncmp(value, "list", ft_strlen(value) + 1) == 0)
	{
		display_translation(1, "command.lang.list", &args, 0);
		list_languages();
		write(2, "\n", 1);
		return (0);
	}
	if (!set_language(value))
	{
		display_translation(2, "command.lang.invalid", &args, 1);
		return (0);
	}
	add_translation_arg(&args, value);
	display_translation(1, "command.lang.success", &args, 1);
	return (0);
}
