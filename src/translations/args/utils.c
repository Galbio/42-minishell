/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 21:36:52 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 22:42:12 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translations.h"

void	add_translation_arg(t_array *args, char *value)
{
	ft_array_push(args, value);
}

int	is_translation_arg(char *value)
{
	return (value[0] == '{'
		&& value[1] && value[1] == '%'
		&& value[2] && value[2] == '}');
}

t_array	base_command_args(char *program_name, char *command_name)
{
	t_array	args;

	args = ft_array();
	add_translation_arg(&args, program_name);
	add_translation_arg(&args, command_name);
	return (args);
}

t_array	simple_arg(char *v)
{
	t_array	args;

	args = ft_array();
	add_translation_arg(&args, v);
	return (args);
}
