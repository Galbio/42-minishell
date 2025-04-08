/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:44:41 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/08 19:15:47 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_readline_keys.h"

static void	register_default(void)
{
	register_special_key(BACKSPACE_KEY, backspace_key);
	register_special_key(UP_ARROW_KEY, previous_history_key);
	register_special_key(DOWN_ARROW_KEY, next_history_key);
	register_special_key(LEFT_ARROW_KEY, move_left_key);
	register_special_key(RIGHT_ARROW_KEY, move_right_key);
	register_special_key(INSERT_KEY, invalid_key);
	register_special_key(WHOME_KEY, home_key);
	register_special_key(DELETE_KEY, delete_key);
	register_special_key(WEND_KEY, end_key);
	register_special_key(BREAKLINE_KEY, breakline_key);
	register_special_key(LHOME_KEY, home_key);
	register_special_key(LEND_KEY, end_key);
	register_special_key(PAGE_UP_KEY, invalid_key);
	register_special_key(PAGE_DOWN_KEY, nofive_buttilde_key);
}

static void	register_controls(void)
{
	register_special_key(CTRL_A_KEY, home_key);
	register_special_key(CTRL_B_KEY, move_left_key);
	register_special_key(CTRL_C_KEY, ctrl_c_key);
	register_special_key(CTRL_D_KEY, ctrl_d_key);
	register_special_key(CTRL_E_KEY, end_key);
	register_special_key(CTRL_F_KEY, move_right_key);
	register_special_key(CTRL_H_KEY, backspace_key);
	register_special_key(CTRL_K_KEY, stash_after_key);
	register_special_key(CTRL_L_KEY, clear_key);
	register_special_key(CTRL_N_KEY, next_history_key);
	register_special_key(CTRL_O_KEY, breakline_key);
	register_special_key(CTRL_P_KEY, previous_history_key);
	register_special_key(CTRL_T_KEY, swap_key);
	register_special_key(CTRL_U_KEY, stash_before_key);
	register_special_key(CTRL_W_KEY, stash_before_in_word_key);
	register_special_key(CTRL_Y_KEY, paste_stash_key);
}

static void	register_special_controls(void)
{
	register_special_key(CTRL_LEFT_ARROW_KEY, previous_word_key);
	register_special_key(CTRL_RIGHT_ARROW_KEY, next_word_key);
	register_special_key(CTRL_UP_ARROW_KEY, invalid_key);
	register_special_key(CTRL_DOWN_ARROW_KEY, invalid_key);
	register_special_key(CTRL_DELETE_KEY, stash_after_in_word_key);
	register_special_key(CTRL_INSERT_KEY, five_tilde_key);
	register_special_key(CTRL_HOME_KEY, invalid_key);
	register_special_key(CTRL_END_KEY, invalid_key);
	register_special_key(CTRL_PAGE_UP_KEY, five_tilde_key);
	register_special_key(CTRL_PAGE_DOWN_KEY, semicolon_five_tilde_key);
}

t_readline	*get_readline_struct(void)
{
	static t_readline	*main = NULL;

	if (!main)
	{
		main = malloc(sizeof(t_readline));
		main->special_keys = ft_array();
		main->stashed = NULL;
		main->cat_stash = 0;
		init_history();
		register_default();
		register_controls();
		register_special_controls();
	}
	return (main);
}
