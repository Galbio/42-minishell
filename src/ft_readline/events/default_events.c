/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:10:51 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/09 19:36:11 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "ft_readline_keys.h"

static void	register_default(void)
{
	ft_readline_register_event(BACKSPACE_KEY, backspace_key);
	ft_readline_register_event(UP_ARROW_KEY, previous_history_key);
	ft_readline_register_event(DOWN_ARROW_KEY, next_history_key);
	ft_readline_register_event(LEFT_ARROW_KEY, move_left_key);
	ft_readline_register_event(RIGHT_ARROW_KEY, move_right_key);
	ft_readline_register_event(INSERT_KEY, invalid_key);
	ft_readline_register_event(WHOME_KEY, home_key);
	ft_readline_register_event(DELETE_KEY, delete_key);
	ft_readline_register_event(WEND_KEY, end_key);
	ft_readline_register_event(BREAKLINE_KEY, breakline_key);
	ft_readline_register_event(LHOME_KEY, home_key);
	ft_readline_register_event(LEND_KEY, end_key);
	ft_readline_register_event(PAGE_UP_KEY, invalid_key);
	ft_readline_register_event(PAGE_DOWN_KEY, nofive_buttilde_key);
}

static void	register_controls(void)
{
	ft_readline_register_event(CTRL_A_KEY, home_key);
	ft_readline_register_event(CTRL_B_KEY, move_left_key);
	ft_readline_register_event(CTRL_C_KEY, ctrl_c_key);
	ft_readline_register_event(CTRL_D_KEY, ctrl_d_key);
	ft_readline_register_event(CTRL_E_KEY, end_key);
	ft_readline_register_event(CTRL_F_KEY, move_right_key);
	ft_readline_register_event(CTRL_H_KEY, backspace_key);
	ft_readline_register_event(CTRL_K_KEY, stash_after_key);
	ft_readline_register_event(CTRL_L_KEY, clear_key);
	ft_readline_register_event(CTRL_N_KEY, next_history_key);
	ft_readline_register_event(CTRL_O_KEY, breakline_key);
	ft_readline_register_event(CTRL_P_KEY, previous_history_key);
	ft_readline_register_event(CTRL_T_KEY, swap_key);
	ft_readline_register_event(CTRL_U_KEY, stash_before_key);
	ft_readline_register_event(CTRL_W_KEY, stash_before_in_word_key);
	ft_readline_register_event(CTRL_Y_KEY, paste_stash_key);
}

static void	register_special_controls(void)
{
	ft_readline_register_event(CTRL_BACKSLASH_KEY, invalid_key);
	ft_readline_register_event(CTRL_LEFT_ARROW_KEY, previous_word_key);
	ft_readline_register_event(CTRL_RIGHT_ARROW_KEY, next_word_key);
	ft_readline_register_event(CTRL_UP_ARROW_KEY, invalid_key);
	ft_readline_register_event(CTRL_DOWN_ARROW_KEY, invalid_key);
	ft_readline_register_event(CTRL_DELETE_KEY, stash_after_in_word_key);
	ft_readline_register_event(CTRL_INSERT_KEY, five_tilde_key);
	ft_readline_register_event(CTRL_HOME_KEY, invalid_key);
	ft_readline_register_event(CTRL_END_KEY, invalid_key);
	ft_readline_register_event(CTRL_PAGE_UP_KEY, five_tilde_key);
	ft_readline_register_event(CTRL_PAGE_DOWN_KEY, semicolon_five_tilde_key);
}

void	ft_readline_register_default_events(void)
{
	register_default();
	register_controls();
	register_special_controls();
}
