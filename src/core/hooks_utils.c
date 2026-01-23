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
#include "mlx.h"
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
}

extern inline t_bool	is_set_bit(unsigned int v, unsigned int flag)
{
	return ((v >> flag) == 1);
}

void	lock_mouse(t_mini_rt *mrt, t_vec3 *pos, int x, int y)
{
	const int w_deadzone = W * DEADZONE;
	const int h_deadzone = H * DEADZONE;

	*pos = (t_vec3) {x, y, 0};
	if (x > (W - (w_deadzone)))
	{
		mlx_mouse_move(mrt->mlx.mlx, mrt->mlx.win, 1 + (w_deadzone), y);
		*pos = (t_vec3) {1 + (w_deadzone), y, 0};
	}
	else if (x < (0 + (w_deadzone)))
	{
		mlx_mouse_move(mrt->mlx.mlx, mrt->mlx.win, W - (w_deadzone), y);
		*pos = (t_vec3) {W - (w_deadzone), y, 0};
	}
	if (y > (H - (h_deadzone)))
	{
		mlx_mouse_move(mrt->mlx.mlx, mrt->mlx.win, x, 1 + (h_deadzone));
		*pos = (t_vec3) {x, 1 + (h_deadzone), 0};
	}
	else if (y < (0 + (h_deadzone)))
	{
		mlx_mouse_move(mrt->mlx.mlx, mrt->mlx.win, x, H - (h_deadzone));
		*pos = (t_vec3) {x, H - (h_deadzone), 0};
	}

}
