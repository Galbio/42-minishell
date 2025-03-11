/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:08:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/11 12:03:25 by lroussel         ###   ########.fr       */
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
	t_vector2	initial_pos;
	t_vector2	pos;
	t_vector2	cursor;
	int			end_line;
	t_vector2	old_tsize;
	char		*buffer_ptr;
	int			exit;
}	t_readline;

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

void		check_resize(t_readline *data, t_vector2 size);

int			clean_readed(char **readed);

void		clear_terminal(int count, int bn_count);
void		update_cursor_position(const char *prompt, t_readline data);
void		on_write(t_readline *data);
void		on_delete(t_readline *data, int deleted);

char		*ft_readline(const char *prompt);

char		*build_result(t_readline data);
int			process_input(t_readline *data, char *buffer);

void		enable_raw_mode(void);
void		disable_raw_mode(void);

int			process_special_keys(t_readline *data, char *buffer);

char		*read_stdin_key(t_readline *readline);

int			count_newlines(t_char *c, t_char *actual, int *lc);
char		get_open_quote(const char *stashed);
void		init_terminal_size(t_vector2 *size);
t_vector2	get_terminal_size(t_readline *data);
int			count_total_newlines(const char *prompt, t_readline data);

t_readline	*get_readline_data(void);
int			ft_readline_must_exit(void);
void		ft_readline_set_exit(int v);
void		ft_readline_sigint(void);
void		ft_readline_init_signals(void);
void		free_ft_readline(t_readline *data);

int			delete_char(t_readline *data);
int			move_cursor_left(t_readline *data);
int			move_cursor_right(t_readline *data);
int			ctrl_c(t_readline *data);
void		ctrl_d(t_readline *data);

#endif
