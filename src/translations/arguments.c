/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:12:13 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/12 14:36:12 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "translations.h"

int	is_translation_argument(char *value)
{
	return (value[0] == '{' && value[1] == '%' && value[2] == '}');
}

t_list	*new_arg(void *value, t_list *next)
{
	t_list	*res;

	res = ft_lstnew(value);
	res->next = next;
	return (res);
}

t_list	*program_arg(char *value, t_list *next)
{
	if (value == NULL)
		return (new_arg("minishell", NULL));
	return (new_arg("minishell", new_arg(value, next)));
}
