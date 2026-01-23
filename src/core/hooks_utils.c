/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:28:00 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/17 16:35:18 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "debug.h"
#include "render.h"
#include "hooks.h"

void	handle_hook_mode(t_mini_rt *mrt, int keysym)
{
	const char	ctrls[HOOKS_MODE_QTY] = {K_RENDER, K_OBJ};
	int			i;

	i = 0;
	while (i < HOOKS_MODE_QTY)
	{
		if (keysym == ctrls[i])
		{
			if (is_set_bit(mrt->mode.v, i))
				mrt->mode.v ^= (1 << i);
			else
				mrt->mode.v |= (1 << i);
			shoot_rays(mrt);
		}
		++i;
	}
	printf("mode: ");
	print_binary(mrt->mode.v);
	printf("\n");
}

extern inline t_bool	is_set_bit(unsigned int v, unsigned int flag)
{
	return ((v >> flag) == 1);
}
