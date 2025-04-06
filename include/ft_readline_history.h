/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_history.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:05:51 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/26 20:15:50 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_HISTORY_H
# define FT_READLINE_HISTORY_H

# include <fcntl.h>

# ifndef HISTORY_SIZE
#  define HISTORY_SIZE 500
# endif

//manager.c
void	add_to_history(char *line);
t_array	get_history(void);
void	free_history_entry(int key, void *value);
int		get_history_maxsize(void);

//writer.c
void	save_history(void);

//reader.c
void	init_history(void);
char	*get_history_file_contents(void);

//path.c
void	set_history_path(char *path);
char	*get_history_path(void);
char	*get_history_path_full(void);

//file.c
void	set_history_filename(char *path);
char	*get_history_filename(void);

//state.c
void	enable_history(void);
void	disable_history(void);
int		is_history_enable(void);

#endif
