/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 06:55:38 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/14 07:17:04 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_var_quote(char *str, t_int_tab *itab)
{
	char	*dest;
	char	*temp;

	temp = get_subcmd(str + itab->i + 1);
	dest = ft_strreplace_part(str, itab->i, ft_strlen(temp) + 3, temp);
	if (str[itab->i + 1] == '\'')
		itab->i += ft_strlen(temp) - 1;
	free(str);
	free(temp);
	return (dest);
}
