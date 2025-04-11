/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:08:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/11 23:56:24 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <termios.h>
# include "libft.h"
# include "ft_readline_history.h"

# define HIDE_CURSOR "\e[?25l"
# define SHOW_CURSOR "\e[?25h"
# define DISPLAY_CURSOR_POSITION "\033[6n"
# define CLEAR_TERMINAL_AFTER_CURSOR "\033[0J"
# define CLEAR_TERMINAL "\033[2J"
# define ERASE_AFTER_CURSOR "\033[K"
# define MOVE_CURSOR_UP "\033[A"
# define MOVE_CURSOR_DOWN "\033[B"
# define MOVE_CURSOR_RIGHT "\033[C"
# define MOVE_CURSOR_LEFT "\033[D"

typedef struct s_readline_char
{
	char					sequence[4];
	struct s_readline_char	*previous;
	struct s_readline_char	*next;
}	t_readline_char;

typedef struct s_readline_data
{
	const char		*prompt;
	char			*buffer_ptr;
	t_readline_char	*first;
	t_readline_char	*current;
	t_readline_char	*current_input;
	t_vector2		pos;
	t_vector2		cursor;
	t_vector2		old_tsize;
	int				update;
	int				exit;
	int				interrupt;
	int				history_index;
	int				display_prompt;
	int				offset;
	int				is_pipe;
	int				tab_pressed;
	t_array			occurences;
}	t_readline_data;

typedef struct s_readline_event
{
	char	*sequence;
	void	(*callback)(t_readline_data *);

}	t_readline_event;

typedef struct s_readline
{
	t_list			*events;
	t_readline_char	*stashed;
	int				cat_stash;
	t_array			history;
}	t_readline;

//autocompletion/commands.c
void			add_builtins_occurences(char *prefix, t_array *occurences,
					int *size);
void			add_path_occurences(char *prefix, char *path,
					t_array *occurences, int *size);

//autocompletion/display.c
void			display_autocompletion(t_readline_data *data);

//autocompletion/research.c
char			*research_autocompletion(t_readline_data *data, char *prefix);

//autocompletion/utils.c
void			add_and_sort_occurence(t_array *occurences, char *value,
					int *size);

//autocompletion/variables.c
void			add_variables_occurences(char *prefix, char *variable,
					t_array *occurences, int *size);

//char/list.c
void			add_char_back(t_readline_char *head, t_readline_char *c);
void			add_char_front(t_readline_char **head, t_readline_char *c);
void			add_char_after(t_readline_char **element, t_readline_char *c);
void			remove_char(t_readline_char **element);

//char/position.c
t_vector2		get_char_pos(t_readline_data *data, t_readline_char *c);

//char/utils.c
t_readline_char	*new_char(char c[4]);
t_readline_char	*last_char(t_readline_char *head);
void			free_chars(t_readline_char *head);

//char/backslashes.c
char			*clean_backslashes(char *build);

//cursor/position/position.c
int				parse_cursor_response(const char *buf, int *row, int *col);
int				get_cursor_position(t_vector2 *pos);

//cursor/position/stdin.c
int				get_cursor_position_from_stdin(int *row, int *col);

//cursor/position/tty.c
int				get_cursor_position_from_tty(int *row, int *col);

//cursor/movements.c
void			move_cursor(t_readline_data *data, int gap);
void			move_x(t_readline_data *data, int gap);
void			move_y(t_readline_data *data, int gap);
void			teleport_cursor(t_vector2 pos);

//cursor/view.c
void			hide_cursor(void);
void			show_cursor(void);

//edition/delete.c
void			on_delete(t_readline_data *data);

//edition/utils.c
void			update_position(t_readline_data *data, t_vector2 size,
					char *build);
void			print_build(char *build);

//edition/write.c
void			on_write(t_readline_data *data);

//extra/env/env.c
void			ft_readline_set_envp_ptr(t_list **envp);
t_list			**ft_readline_get_envp_ptr(void);

//extra/env/path.c
void			ft_readline_set_path_ptr(char ***path);
char			***ft_readline_get_path_ptr(void);

//extra/erase.c
void			erase_after_cursor(int fd, int new_line);

//extra/fd.c
int				get_extra_data_in_fd(void);
int				get_extra_data_out_fd(void);

//extra/raw_mode.c
void			enable_raw_mode(void);
void			disable_raw_mode(void);

//extra/size.c
void			init_terminal_size(t_vector2 *size);
t_vector2		get_terminal_size(t_readline_data *data, int check_resize);

//format/checker.c
void			ft_readline_set_check_format(int v);
int				ft_readline_is_format_checked(void);
int				check_quotes(const char *build);
int				check_backslashes(const char *build);

//format/lines_count
int				count_low_newlines(t_readline_data *data, t_readline_char *to);
int				count_hard_newlines(t_readline_data data, t_readline_char *to);

//process/converter.c
char			*list_to_string(t_readline_data data, t_readline_char *to);
int				is_first_argument(t_readline_char *position);
char			*get_argument_before(t_readline_char *position);

//process/handler.c
int				handle_key_input(t_readline_data *data, char *buffer);

//process/processor.c
int				process_input(t_readline_data *data, char last_c);
int				process_default_key(t_readline_data *data, char *buffer);

//process/reader.c
int				read_stdin_keys(char *buffer);

//process/stash.c
void			add_to_stash(t_readline_char **stashed, t_readline_char *node,
					int type);
void			clean_stash(t_readline *main, int check_cat);

//events/default/autocompletion.c
void			tab_key(t_readline_data *data);

//events/default/breakline.c
void			breakline_key(t_readline_data *data);

//events/default/clear.c
void			clear_key(t_readline_data *data);

//events/default/delete.c
void			backspace_key(t_readline_data *data);
void			delete_key(t_readline_data *data);

//events/default/five_tilde.c
void			five_tilde_key(t_readline_data *data);
void			semicolon_five_tilde_key(t_readline_data *data);
void			nofive_buttilde_key(t_readline_data *data);

//events/default/history.c
void			previous_history_key(t_readline_data *data);
void			next_history_key(t_readline_data *data);

//events/default/interrupt.c
void			ctrl_c_key(t_readline_data *data);
void			ctrl_d_key(t_readline_data *data);

//events/default/invalid.c
void			invalid_key(t_readline_data *data);

//events/default/move.c
void			move_left_key(t_readline_data *data);
void			move_right_key(t_readline_data *data);

//events/default/stash_word.c
void			stash_before_in_word_key(t_readline_data *data);
void			stash_after_in_word_key(t_readline_data *data);

//events/default/stash.c
void			stash_before_key(t_readline_data *data);
void			stash_after_key(t_readline_data *data);
void			paste_stash_key(t_readline_data *data);

//events/default/swap.c
void			swap_key(t_readline_data *data);

//events/default/teleport.c
void			home_key(t_readline_data *data);
void			end_key(t_readline_data *data);
void			previous_word_key(t_readline_data *data);
void			next_word_key(t_readline_data *data);

//events/factory.c
void			ft_readline_register_event(char *sequence,
					void (*callback)(t_readline_data *));
int				ft_readline_execute_events(t_readline_data *data,
					char *sequence);

//events/default_events.c
void			ft_readline_register_default_events(void);

//exit.c
int				ft_readline_must_exit(void);
void			ft_readline_set_exit(int v);
void			free_readline(void);
void			free_readline_data(t_readline_data *data);

//ft_readline.c
char			*ft_readline(const char *prompt);

//initialization.c
t_readline_data	*get_readline_data(void);
void			init_readline_data(const char *prompt, t_readline_data *data);

//main.c
t_readline		*get_readline_struct(void);

#endif
