/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_core.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:44:41 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/15 22:34:11 by lroussel         ###   ########.fr       */
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
		register_special_key(BACKSPACE_KEY, backspace_key);
		register_special_key(LEFT_ARROW_KEY, left_arrow_key);
		register_special_key(RIGHT_ARROW_KEY, right_arrow_key);
		register_special_key(HOME_KEY, home_key);
		register_special_key(DELETE_KEY, delete_key);
		register_special_key(END_KEY, end_key);
		register_special_key("\n", breakline_key);
		register_special_key(CTRL_A, home_key);
		register_special_key(CTRL_B, left_arrow_key);
		register_special_key(CTRL_C, ctrl_c_key);
		register_special_key(CTRL_D, ctrl_d_key);
		register_special_key(CTRL_E, end_key);
		register_special_key(CTRL_F, right_arrow_key);
		register_special_key(CTRL_G, invalid_key);
		register_special_key(CTRL_H, backspace_key);
		register_special_key(CTRL_I, invalid_key);
		register_special_key(CTRL_K, stash_after_key);
		register_special_key(CTRL_L, clear_key);
		register_special_key(CTRL_N, invalid_key);
		register_special_key(CTRL_O, breakline_key);
		register_special_key(CTRL_P, invalid_key);
		register_special_key(CTRL_R, invalid_key);
		register_special_key(CTRL_T, swap_key);
		register_special_key(CTRL_U, stash_before_key);
		register_special_key(CTRL_V, invalid_key);
		register_special_key(CTRL_W, stash_before_in_word_key);
		register_special_key(CTRL_X, invalid_key);
		register_special_key(CTRL_Y, paste_stash_key);
		register_special_key(CTRL_Z, invalid_key);
	}
	return (core);
}
