/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:07:29 by gakarbou          #+#    #+#             */
/*   Updated: 2025/03/02 22:39:21 by gakarbou         ###   ########.fr       */
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

t_int_tab	init_int_tab(void);

t_list		*parse_envp(char **envp, t_main_envp *imp);
char		*parse_var(char *var_name, t_list *envp, t_main_envp *imp);
char		*parse_commands(char *str, t_list *envp, t_main_envp *imp);
char		check_built_in(char **name);
void		handle_var(char *str, t_int_tab *infos,
				t_list *envp, t_main_envp *imp);
char		*get_var_str(char *str);
char		*handle_bquotes(char *res);

//exec_command.c
int			get_command_argc(char *str);
char		*execute_command(char **argv, t_main_envp *imp);
char		**create_command_argv(char *str, t_list *envp, t_main_envp *imp);

#endif
