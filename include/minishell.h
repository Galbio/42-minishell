/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:07:29 by gakarbou          #+#    #+#             */
/*   Updated: 2025/02/23 21:29:02 by gakarbou         ###   ########.fr       */
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
# include <curses.h>
# include <term.h>
# include <unistd.h>

# include "libft.h"
# include "readline.h"

//TODO: move gnl to libft
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_main_envp
{
	char	**envp_cpy;
	char	**path;
	char	*home;
	char	*cwd;
	int		shell_level;
}	t_main_envp;

typedef struct s_command
{
	char	*command;
	char	*flags;
}	t_command;

typedef struct s_int_tab
{
	int		i;
	int		res;
	int		ret;
	char	cur_quote;
	char	backslash;
	char	*ptr1;
	char	*ptr2;
}	t_int_tab;

void		launch(t_list *envp, t_main_envp *imp);

char		*parse_quotes(char *str, t_list *envp, t_main_envp *imp);
char		check_special_char(char c, char *backslash, char *cur_quote);

//TODO: move ft_readline to libft
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char		*ft_securejoin(char const *s1, char const *s2, char must_free);
int			ft_securelen(char const *str);

//TODO: move to libft
int			ft_is_quote(int c);
int			ft_is_whitespace(int c);
t_int_tab	init_int_tab(void);

char		*get_next_line(int fd);
char		*create_line(int byte_read, char **stashed, char **buffer);
char		*recover_stashed(char *buffer, char *stashed);
char		*seperate(char *buffer, char **stashed);
void		*on_error(char **buffer, char **stashed);
t_list		*parse_envp(char **envp, t_main_envp *imp);
char		*parse_var(char *var_name, t_list *envp, t_main_envp *imp);
char		*parse_commands(char *str, t_list *envp, t_main_envp *imp);
char		check_built_in(char **name);

//exec_command.c
int			get_command_argc(char *str);
char		**create_command_argv(char *str, t_list *envp, t_main_envp *imp);
char		*execute_command(char *str, t_list *envp, t_main_envp *imp);

char		*ft_cd(char *command);
char		*ft_echo(char *command);
char		*ft_pwd(void);


#endif
