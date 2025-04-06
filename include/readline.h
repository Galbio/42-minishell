/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:08:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/06 12:45:02 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <signal.h>
# include "libft.h"
# include "readline_history.h"

# define HIDE_CURSOR "\e[?25l"
# define SHOW_CURSOR "\e[?25h"
# define CLEAR_TERMINAL "\033[2J"

typedef struct s_char
{
	char			c[4];
	struct s_char	*previous;
	struct s_char	*next;
}	t_char;

typedef struct s_readline_data
{
	const char	*prompt;
	char		*buffer_ptr;
	t_char		*first;
	t_char		*actual;
	t_char		*current_input;
	t_vector2	pos;
	t_vector2	cursor;
	t_vector2	old_tsize;
	int			update;
	int			exit;
	int			interrupt;
	int			history_index;
	int			display_prompt;
	int			offset;
	int			is_pipe;
}	t_readline_data;

typedef struct s_special_key
{
	char	*sequence;
	void	(*callback)(t_readline_data *);

}	t_special_key;

typedef struct s_readline
{
	t_special_key	**special_keys;
	t_char			*stashed;
	int				cat_stash;
	t_array			history;
}	t_readline;

int				handle_key_input(t_readline_data *data, char *buffer);

void			add_char_back(t_char *head, t_char *c);
void			add_char_front(t_char **head, t_char *c);
void			add_char_after(t_char **element, t_char *c);
void			add_char_before(t_char *element, t_char *c);
void			remove_char(t_char **element);

t_char			*new_char(char c[4]);
t_char			*last_char(t_char *head);
void			free_chars(t_char *head);

void			move_cursor(t_readline_data *data, int gap);
void			move_x(t_readline_data *data, int gap);
void			move_y(t_readline_data *data, int gap);
void			teleport_cursor(t_vector2 pos);

int				get_cursor_position(t_vector2 *pos);
int				get_cursor_position_from_stdin(int *row, int *col);

int				clean_readed(char **readed);

void			update_position(t_readline_data *data, t_vector2 size, char *build);
void			print_build(char *build);

void			on_write(t_readline_data *data);
void			on_delete(t_readline_data *data);

char			*ft_readline(const char *prompt);

char			*build_result(t_readline_data data, t_char *to);
int				process_input(t_readline_data *data, char last_c);

int				process_default_key(t_readline_data *data, char *buffer);

void			enable_raw_mode(void);
void			disable_raw_mode(void);

void			read_stdin_keys(char *buffer);

int				check_quotes(const char *build);
int				check_backslashes(const char *build);
char			*clean_backslashes(char *build);
void			init_terminal_size(t_vector2 *size);
t_vector2		get_terminal_size(t_readline_data *data, int check_resize);
int				count_low_newlines(t_readline_data *data, t_char *to);
int				count_hard_newlines(t_readline_data data, t_char *to);
t_vector2		actual_char_pos(t_readline_data *data);

char			*last_newline(char *build);
t_vector2		get_char_pos(t_readline_data *data, t_char *c);

t_readline	*aaaaaaaaaaaaaaaaaaa(void);

void			register_special_key(char *sequence,
					void (*callback)(t_readline_data *));
t_special_key	*get_by_sequence(char *sequence);
int				get_special_keys_count(void);
t_special_key	**get_special_keys(void);

void			invalid_key(t_readline_data *data);
void			backspace_key(t_readline_data *data);
void			move_left_key(t_readline_data *data);
void			move_right_key(t_readline_data *data);
void			home_key(t_readline_data *data);
void			delete_key(t_readline_data *data);
void			end_key(t_readline_data *data);
void			breakline_key(t_readline_data *data);
void			ctrl_c_key(t_readline_data *data);
void			ctrl_d_key(t_readline_data *data);
void			stash_before_key(t_readline_data *data);
void			stash_after_key(t_readline_data *data);
void			stash_before_in_word_key(t_readline_data *data);
void			stash_after_in_word_key(t_readline_data *data);
void			paste_stash_key(t_readline_data *data);
void			clear_key(t_readline_data *data);
void			swap_key(t_readline_data *data);
void			previous_word_key(t_readline_data *data);
void			next_word_key(t_readline_data *data);
void			five_tilde_key(t_readline_data *data);
void			semicolon_five_tilde_key(t_readline_data *data);
void			previous_history_key(t_readline_data *data);
void			next_history_key(t_readline_data *data);

t_readline_data		*get_readline_data(void);
int				ft_readline_must_exit(void);
void			ft_readline_set_exit(int v);
void			ft_readline_sigint(void);
void			ft_readline_init_signals(void);
void			free_readline_core(void);
void			free_readline_data(t_readline_data *data);

void			add_to_stash(t_char **stashed, t_char *node, int type);
void			clean_stash(t_readline *core, int check_cat);

void			hide_cursor(void);
void			show_cursor(void);

int				get_extra_data_in_fd(void);
int				get_extra_data_out_fd(void);

#endif
