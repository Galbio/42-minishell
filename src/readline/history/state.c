/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:17:10 by lroussel          #+#    #+#             */
/*   Updated: 2025/03/26 18:34:17 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	hstate(int value)
{
	static int	state = 0;

	if (value == 0 || value == 1)
		state = value;
	return (state);
}

void	enable_history(void)
{
	hstate(1);
}

void	disable_history(void)
{
	hstate(0);
}

int	is_history_enable(void)
{
	return (hstate(-1));
}
