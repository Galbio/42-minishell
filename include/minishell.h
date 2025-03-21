/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:07:29 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/17 20:09:59 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
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

typedef struct s_main_envp
{
	unsigned char	exit_status;
	char			**envp_cpy;
	char			**path;
	char			*home;
	char			is_bquoted;
	int				shell_level;
	int				output_fd;
}	t_main_envp;

typedef struct s_cmd_params
{
	char		**argv;
	t_list		**envp;
	t_main_envp	*imp;
}	t_cmd_params;

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

void			launch(t_list *envp, t_main_envp *imp);

char			*parse_quotes(char *str, t_list *envp, t_main_envp *imp);
char			check_special_char(char c, char *backslash, char *cur_quote);
void			free_envp(t_list **envp, t_main_envp *imp);

t_int_tab		init_int_tab(void);

t_list			*parse_envp(char **envp, t_main_envp *imp);
char			*parse_var(char *var_name, t_list **envp, t_main_envp *imp);
char			*parse_commands(char *str, t_list *envp, t_main_envp *imp);
char			*read_whole_fd(int fd);
void			handle_var(char *str, t_int_tab *infos, t_list **output);
char			*handle_bquotes(char *res);
char			*clean_whitespaces(char *str);
char			*get_var_str(char *str);
t_list			*init_pipes(char *str, t_list **envp, t_main_envp *imp);
t_list			*split_semicolon(char *str);

//commands
void			execute_line(t_list *commands, t_list **envp,
					t_main_envp *imp);
int				execute_pipes(t_list *commands, t_list **envp,
					t_main_envp *imp);
void			execute_bin(char **argv, t_main_envp *imp);
char			**create_command_argv(char *str, t_list **envp,
					t_main_envp *imp);

//pipe utils
t_cmd_params	make_cmd(void *argv_ptr, t_list **envp, t_main_envp *imp);
int				wait_line_end_exec(int nb_cmd, int write_pipe,
					int read_pipe, pid_t pid);
void			go_to_next_command(t_list **commands, int *temp, int pipes[2]);
char			check_builtins(char *name);
int				handle_builtins(int code, t_cmd_params *cmd);
char			go_to_var_end(char *str, int *i);

//builtins
int				ms_cd(t_cmd_params *cmd);
int				ms_echo(t_cmd_params *cmd);
int				ms_pwd(void);
int				ms_unset(t_cmd_params *cmd);
int				ms_exit(t_cmd_params *cmd);
int				ms_export(t_cmd_params *cmd);
int				ms_env(t_cmd_params *cmd);

//builtins additional
void			export_vars(t_list *envp);
void			unset_var(char *name, t_list **envp, t_main_envp *imp);

void			init_signals(void);

#endif
