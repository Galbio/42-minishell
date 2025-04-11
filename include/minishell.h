/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:07:29 by gakarbou          #+#    #+#             */
/*   Updated: 2025/04/11 18:53:48 by gakarbou         ###   ########.fr       */
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
# include "ft_readline.h"

# ifndef ZSH
#  define ZSH 0
# endif

typedef struct s_main_envp
{
	char			**path;
	char			*home;
	int				shell_level;
	int				output_fd;
	int				input_fd;
	long			actual_pos;
	t_list			*heredocs_infos;
	t_list			*aliases;
}	t_main_envp;

typedef struct s_cmd_params
{
	char		**argv;
	t_list		*redir;
	t_list		**envp;
	t_main_envp	*imp;
	t_list		*pipes;
	t_list		*cmds;
	t_list		*sep;
	t_list		**extra;
}	t_cmd_params;

typedef struct s_redirection
{
	int			is_fd;
	char		*og_str;
	char		*method;
	char		**values;
}	t_redirection;

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

typedef struct s_research
{
	char				*addr;
	int					len;
	t_list				*matches;
	struct s_research	*next;
}	t_research;

void			launch(t_list *envp, t_main_envp *imp);

//signals
void			on_sigint(t_readline_data *data);
void			init_signals(void);

//exit status
void			set_exit_status(int status);
int				get_exit_status(void);
int				get_depth(int v);

//misc
t_int_tab		init_int_tab(void);
char			check_special_char(char *str, t_int_tab *itab);

//free functions
void			free_cmd(t_cmd_params *cmd, char mode);
void			free_envp(t_list **envp, t_main_envp *imp);
char			free_redir(t_list *cur, char res);
void			free_regex_match(t_research *regex);

//parsing
char			*handle_bquotes(char *res);
void			split_cmds(char *res, t_list **cmds);
t_list			*split_pipes(char *str);
t_list			*split_separators(char *str, t_list **sep);
int				add_cmd(char *str, t_list **dest, t_int_tab *itab);
char			*get_subcmd(char *str);
int				get_subcmd_size(char *str);
int				handle_separator(char *str, t_list **sep);
char			*handle_aliases(char *input, t_list *aliases);

//braces
char			*handle_brace_option(char *str, t_cmd_params *cmd, char *src);
char			*if_not_defined(char *src, char *default_str, t_cmd_params *cmd);
char			*assign_if_not_defined(char *src, char *default_str,
					t_cmd_params *cmd);
char			*if_defined(char *src, char *default_str, t_cmd_params *cmd);
char			*error_if_not_defined(char *src, char *default_str,
					t_cmd_params *cmd);

//redirections
char			handle_redirections(t_cmd_params *cmd);
char			redirect_stdout(t_redirection *ret);
char			is_only_nb(char *str);
char			*get_var_value(char *name, t_list *cur);

//heredoc
char			*parse_heredoc_value(char *str, t_main_envp *imp);
char			*identify_heredoc(char *str, t_list **heredocs,
					t_main_envp *imp);
char			*parse_heredoc_quote(char *str);
void			free_heredocs(t_list *cur);
void			add_heredoc_history(t_list *cur, t_list **end);
char			advance_itab(char *str, t_int_tab *itab, char *ignore_tab);
char			*wait_value(t_list **heredocs, char *value, char ignore_tab);
char			*add_line(char *content, char *line);

//envp
t_list			*parse_envp(char **envp, t_main_envp *imp);
char			**create_envp_cpy(t_list **envp, t_main_envp *imp);

//variables
char			*parse_var(char *var_name, t_list **envp, t_main_envp *imp);
char			*parse_commands(char *str, t_list *envp, t_main_envp *imp);
char			*get_var_str(char *str);
char			*get_var_name(char *str);

//commands
void			execute_line(char *str, t_list **envp,
					t_main_envp *imp);
int				execute_command(t_list *commands, t_cmd_params *params,
					t_list *cmd_lst, t_list *sep);
int				execute_pipes(t_cmd_params *cmd);
int				execute_subshell(t_cmd_params *cmd);
int				execute_single_bin(t_cmd_params *cmd, int is_env);
void			execute_bin(t_cmd_params *cmd, int is_env);

//argv
t_cmd_params	*create_command_argv(t_cmd_params *cmd);
t_list			*fill_argv(char *str, t_cmd_params *cmd);
char			**fill_return_argv(t_list *argv);
void			handle_var(char *str, t_int_tab *itab, t_list **cmd_outputs,
					t_cmd_params *cmd);
void			add_to_argv(t_list **dest, char *str, t_int_tab *itab,
					t_cmd_params *cmd);
void			add_splitted_to_add(char *str, t_list **dest);
char			*parse_var_return(char *str, char quote);
char			*parse_quotes(char *str, t_cmd_params *cmd);
char			*make_splitted_str(char **str, int *i, char is_sep);
void			add_redirection(char *str, t_int_tab *itab,
					t_cmd_params *cmd, t_list **dest);
void			handle_local_appending(char *str, t_int_tab *itab,
					t_cmd_params *cmd);
char			*handle_commands(t_int_tab *itab, t_cmd_params *cmd,
					t_list **outputs);

//pipe utils
t_cmd_params	*make_cmd(void *argv_ptr, t_list **envp, t_main_envp *imp);
char			check_builtins(char *name);
int				handle_builtins(int code, t_cmd_params *cmd);
int				go_to_var_end(char *str);
char			*trim_ws(char *str);

//builtins
int				ms_cd(t_cmd_params *cmd);
int				ms_echo(t_cmd_params *cmd);
int				ms_pwd(void);
int				ms_unset(t_cmd_params *cmd);
int				ms_exit(t_cmd_params *cmd);
int				ms_export(t_cmd_params *cmd);
int				ms_env(t_cmd_params *cmd);
int				ms_alias(t_cmd_params *cmd);

//builtins additional
void			export_vars(t_list *envp);
void			unset_var(char *name, t_list **envp, t_main_envp *imp);
void			change_envp_pwd(t_list **envp, char *name);

void			init_regexs(void);
t_list			*search_pattern(char *path, char *pattern);
t_list			*search_pattern_recursive(char *base_path, char **path);
t_research		*parse_research(char *value);

#endif
