/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 06:55:38 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/14 08:37:09 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_var_quote(char *str, t_int_tab *itab)
{
	char	*dest;

	dest = ft_strreplace_part(str, itab->i--, 1, "");
	free(str);
	return (dest);
}
