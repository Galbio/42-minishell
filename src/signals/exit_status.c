/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:45:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/11 18:33:45 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	exit_status(int v)
{
	static int	status = 0;

	if (v >= 0)
		status = v;
	return (status);
}

void	set_exit_status(int status)
{
	exit_status(status);
}

int	get_exit_status(void)
{
	return (exit_status(-1));
}
