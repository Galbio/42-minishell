/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_core.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:44:41 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/14 23:52:19 by lroussel         ###   ########.fr       */
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
		register_special_key(BACKSPACE_KEY, on_press_backspace_key);
		register_special_key(LEFT_ARROW_KEY, on_press_left_arrow_key);
		register_special_key(RIGHT_ARROW_KEY, on_press_right_arrow_key);
		register_special_key(HOME_KEY, on_press_home_key);
		register_special_key(DELETE_KEY, on_press_delete_key);
		register_special_key(END_KEY, on_press_end_key);
		register_special_key("\n", on_press_breakline_key);
		register_special_key(CTRL_A, on_press_invalid_key);
		register_special_key(CTRL_B, on_press_left_arrow_key);
		register_special_key(CTRL_C, on_press_ctrl_c_key);
		register_special_key(CTRL_D, on_press_ctrl_d_key);
		register_special_key(CTRL_E, on_press_invalid_key);
		register_special_key(CTRL_F, on_press_invalid_key);
		register_special_key(CTRL_G, on_press_invalid_key);
		register_special_key(CTRL_H, on_press_invalid_key);
		register_special_key(CTRL_I, on_press_invalid_key);
//		register_special_key(CTRL_J, on_press_invalid_key);
		register_special_key(CTRL_K, on_press_invalid_key);
		register_special_key(CTRL_L, on_press_invalid_key);
//		register_special_key(CTRL_M, on_press_invalid_key);
		register_special_key(CTRL_N, on_press_invalid_key);
		register_special_key(CTRL_O, on_press_breakline_key);
		register_special_key(CTRL_P, on_press_invalid_key);
		register_special_key(CTRL_R, on_press_invalid_key);
		register_special_key(CTRL_T, on_press_invalid_key);
		register_special_key(CTRL_U, on_press_invalid_key);
		register_special_key(CTRL_V, on_press_invalid_key);
		register_special_key(CTRL_W, on_press_invalid_key);
		register_special_key(CTRL_X, on_press_invalid_key);
		register_special_key(CTRL_Y, on_press_invalid_key);
	}
	return (core);
}
