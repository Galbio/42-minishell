/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:08:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/12 15:16:46 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <termios.h>
# include "libft.h"

# define DELETE_KEY "\x7F"
# define LEFT_ARROW_KEY "\x1B[D"
# define RIGHT_ARROW_KEY "\x1B[C"
# define HOME_KEY "\x1B[H"
# define END_KEY "\x1B[F"
# define PAGE_UP_KEY "\x1B[5~"
# define PAGE_DOWN_KEY "\x1B[6~"

typedef struct s_char
{
	int				c;
	struct s_char	*previous;
	struct s_char	*next;
}	t_char;

typedef struct s_readline
{
	const char	*prompt;
	t_char		*first;
	t_char		*actual;
	int			update;
	int			size;
	t_vector2	pos;
	t_vector2	cursor;
	t_vector2	old_tsize;
}	t_readline;

typedef struct s_special_key
{
	char	*sequence;
	int	(*callback)(t_readline *);

}	t_special_key;

typedef struct s_main
{
	t_special_key	**special_keys;
}	t_readline_core;

void		handle_key_input(t_readline *data, char *buffer);

void		add_char_back(t_char *head, t_char *c);
void		add_char_front(t_char **head, t_char *c);
void		add_char_after(t_char **element, t_char *c);
void		add_char_before(t_char *element, t_char *c);
void		remove_char(t_char **element);

t_char		*new_char(int c);
t_char		*last_char(t_char *head);

void		move_cursor(t_readline *data, int gap);
void		move_x(t_readline *data, int gap);
void		move_y(t_readline *data, int gap);
void		teleport_cursor(t_vector2 pos);

int			get_cursor_position(t_vector2 *pos);

int			clean_readed(char **readed);

void		on_write(t_readline *data, char c);
void		on_delete(t_readline *data);

char		*ft_readline(const char *prompt);

char		*build_result(t_readline data, t_char *to);
int			process_input(t_readline *data, char *buffer);

void		enable_raw_mode(struct termios *raw);
void		disable_raw_mode(struct termios *raw);

void		read_stdin_keys(char *buffer);

char		get_open_quote(const char *stashed);
void		init_terminal_size(t_vector2 *size);
t_vector2	get_terminal_size(t_readline *data, int check_resize);
int			count_low_newlines(t_readline *data, t_char *to);
int			count_hard_newlines(t_readline data, t_char *to);
t_vector2	actual_char_pos(t_readline *data);

char		*last_newline(char *build);
t_vector2	get_char_pos(t_readline *data, t_char *c);

t_readline_core		*get_readline_core(void);

void		register_special_key(char *sequence, int (*callback)(t_readline *));
t_special_key	*get_by_sequence(char *sequence);
int			get_special_keys_count(void);
t_special_key	**get_special_keys(void);

int	on_press_delete_key(t_readline *data);
int	on_press_left_arrow_key(t_readline *data);
int	on_press_right_arrow_key(t_readline *data);
int	on_press_home_key(t_readline *data);
int	on_press_end_key(t_readline *data);

#endif
