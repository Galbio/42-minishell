/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_int_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:13:40 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/23 13:33:50 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_int_tab	init_int_tab(void)
{
	t_int_tab	p;

	p.i = -1;
	p.res = 0;
	p.ret = 0;
	p.backslash = 0;
	p.cur_quote = 0;
	p.ptr1 = NULL;
	p.ptr2 = NULL;
	return (p);
}
