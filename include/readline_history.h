/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_history.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:05:51 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/26 14:10:40 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_HISTORY_H
# define READLINE_HISTORY_H

# include <fcntl.h>

# define HISTORY_PATH "./.minishell_history"
# define HISTORY_SIZE 500

//manager.c
void	add_history(char *line);
t_array	get_history(void);
void	free_history(int key, void *value);
void	save_history(void);

//reader.c
void	init_history(void);
char	*get_history_file_contents(void);

#endif
