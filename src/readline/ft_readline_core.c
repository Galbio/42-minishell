/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_core.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:44:41 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/14 15:53:15 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

t_readline_core	*get_readline_core(void)
{
	static t_readline_core	*core = NULL;

	if (!core)
	{
		core = malloc(sizeof(t_readline_core));
		core->special_keys = malloc(sizeof(t_special_key *));
		core->special_keys[0] = NULL;
		register_special_key(DELETE_KEY, on_press_delete_key);
		register_special_key(LEFT_ARROW_KEY, on_press_left_arrow_key);
		register_special_key(RIGHT_ARROW_KEY, on_press_right_arrow_key);
		register_special_key(HOME_KEY, on_press_home_key);
		register_special_key(END_KEY, on_press_end_key);
		register_special_key("\n", on_press_breakline_key);
		register_special_key(CTRL_C, on_press_ctrl_c_key);
		register_special_key(CTRL_D, on_press_ctrl_d_key);
	}
	return (core);
}
