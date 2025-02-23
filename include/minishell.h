/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:07:29 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/23 04:18:30 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/resource.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "libft.h"
# include <unistd.h>

void	launch(void);

//TODO: move ft_readline to libft
char	*ft_readline(const char *prompt);
int		clean_readed(char **readed);

//TODO: move ft_readline to libft
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

//TODO: move to libft
int		ft_is_quote(int c);
int		ft_is_whitespace(int c);

//TODO: move gnl to libft
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*create_line(int byte_read, char **stashed, char **buffer);
char	*recover_stashed(char *buffer, char *stashed);
char	*seperate(char *buffer, char **stashed);
void	*on_error(char **buffer, char **stashed);

void	launch(void);

#endif
