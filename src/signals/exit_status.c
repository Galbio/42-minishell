/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:45:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/04/09 19:56:46 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static unsigned char	exit_status(int v)
{
	static unsigned char	status = 0;

	if (v >= 0)
		status = v;
	return (status);
}

void	set_exit_status(unsigned char status)
{
	exit_status(status);
}

unsigned char	get_exit_status(void)
{
	return (exit_status(-1));
}
