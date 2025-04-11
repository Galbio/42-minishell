/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 00:58:41 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/12 01:05:53 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	cwd_error(char *title)
{
	write(2, title, ft_strlen(title));
	write(2, "error retrieving current directory: getcwd: cannot", 50);
	write(2, " access parent directories: No such file or directory\n", 54);
}
