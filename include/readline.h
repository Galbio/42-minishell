/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:08:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/24 14:54:25 by lroussel         ###   ########.fr       */
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

typedef struct s_char
{
	int				c;
	struct s_char	*previous;
	struct s_char	*next;
}	t_char;

//TODO: libft
typedef struct s_vector2
{
	int	x;
	int	y;
}	t_vector2;

typedef struct s_readline
{
	t_char		*first;
	t_char		*actual;
	int			update;
	int			c;
	int			size;
	t_vector2	pos;
	t_vector2	cursor;
}	t_readline;

//TODO: move ft_readline to libft

int			process_special_keys(t_readline *data);
void		handle_key_input(t_readline *data, char buffer[100]);

void		add_char_back(t_char *head, t_char *c);
void		add_char_front(t_char **head, t_char *c);
void		add_char_after(t_char **element, t_char *c);
void		add_char_before(t_char *element, t_char *c);
void		remove_char(t_char **element);

t_char		*new_char(int c);
t_char		*last_char(t_char *head);

void		move_cursor(t_vector2 *pos, int gap);
void		move_x(t_vector2 *pos, int gap);
void		move_y(t_vector2 *pos, int gap);
void		teleport_cursor(t_vector2 pos);

int			get_cursor_position(t_vector2 *pos);

int			clean_readed(char **readed);

void		clear_terminal(int count, int bn_count);
void		update_cursor_position(const char *prompt, t_readline data);
void		on_write(t_readline *data);
void		on_delete(t_readline *data, int deleted);
t_vector2	get_position(const char *prompt, t_readline data);

char		*ft_readline(const char *prompt);

char		*build_result(t_readline data);
int			process_input(t_readline *data);

void		enable_raw_mode(struct termios *raw);
void		disable_raw_mode(struct termios *raw);

int			count_newlines(t_char *c, t_char *actual, int *lc);
char		get_open_quote(const char *stashed);
t_vector2	get_terminal_size(void);
int			count_total_newlines(const char *prompt, t_readline data);

int			ft_abs(int v);

#endif
