/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:39:49 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/17 16:31:10 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysymdef.h>
#include "mlx.h"
#include "hooks.h"
#include "vec3.h"
#include "render.h"
#include "core.h"

int	handle_mouse_move(int x, int y, void *param)
{
	t_mini_rt		*mini_rt;
	const t_vec3	mouse = {x, y, VP_DISTANCE};
	static t_vec3	center = {(double)W / 2, (double)H / 2, 0};
	t_vec3			dir;

	dir = vec3_normalize(vec3_sub(mouse, center));
	dir = vec3_scale(dir, SENSITIVITY);
	mini_rt = (t_mini_rt *)param;
	if (is_set_bit(mini_rt->mode.v, OBJ))
		mlx_mouse_show(mini_rt->mlx.mlx, mini_rt->mlx.win);
	else if (!is_set_bit(mini_rt->mode.v, RENDER))
	{
		mini_rt->cam.dir = vec3_add(mini_rt->cam.dir, dir);
		center = mouse;
		shoot_rays(mini_rt);
	}
	return (0);
}

int	handle_mouse_scroll(int mouse_event, void *param)
{
	t_mini_rt		*mini_rt;
	const double	step = 0.02;

	mini_rt = (t_mini_rt *)param;
	if (is_set_bit(mini_rt->mode.v, RENDER))
		return (0);
	if (mouse_event == ON_MOUSEDOWN)
	{
		if (rad_to_deg(mini_rt->cam.fov - step) > MIN_FOV_DEG)
			mini_rt->cam.fov -= step;
	}
	else if (mouse_event == ON_MOUSEUP)
	{
		if (rad_to_deg(mini_rt->cam.fov + step) < MAX_FOV_DEG)
			mini_rt->cam.fov += step;
	}
	shoot_rays(mini_rt);
	return (0);
}

static int	handle_move_keypress(int keysym, void *param)
{
	t_mini_rt		*mrt;
	const double	s = 2;

	mrt = (t_mini_rt *)param;
	if (keysym == K_UP)
		mrt->cam.ori = vec3_sub(mrt->cam.ori, vec3_scale(mrt->cam.up, s));
	else if (keysym == K_DOWN)
		mrt->cam.ori = vec3_add(mrt->cam.ori, vec3_scale(mrt->cam.up, s));
	else if (keysym == K_RIGHT)
		mrt->cam.ori = vec3_add(mrt->cam.ori, vec3_scale(mrt->cam.right, s));
	else if (keysym == K_LEFT)
		mrt->cam.ori = vec3_sub(mrt->cam.ori, vec3_scale(mrt->cam.right, s));
	else if (keysym == K_FORWARD)
		mrt->cam.ori = vec3_add(mrt->cam.ori, vec3_scale(mrt->cam.dir, s));
	else if (keysym == K_BACKWARD)
		mrt->cam.ori = vec3_sub(mrt->cam.ori, vec3_scale(mrt->cam.dir, s));
	else if (keysym == K_RESET)
	{
		mrt->cam.ori.x = 0;
		mrt->cam.ori.y = 0;
		mrt->cam.ori.z = 0;
		mrt->cam.dir.x = 0;
		mrt->cam.dir.y = 0;
		mrt->cam.dir.z = VP_DISTANCE;
	}
	return (0);
}

/**
	* @brief Handles keypress events.
* @param keysym The key symbol of the pressed key.
* @param mini_rt Pointer to the miniRT structure.
* @return 0 on success.
* @note Exits the program if the Escape 65307 key / q 113 key is pressed.
*/
int	handle_keypress(int keysym, void *param)
{
	t_mini_rt	*mini_rt;

	mini_rt = (t_mini_rt *)param;
	handle_hook_mode(mini_rt, keysym);
	if (keysym == ESCAPE)
		clean_exit(mini_rt, SUCCESS);
	else if (is_set_bit(mini_rt->mode.v, RENDER))
		return (0);
	handle_move_keypress(keysym, param);
	shoot_rays(mini_rt);
	return (0);
}

int	handle_window_close(void *param)
{
	t_mini_rt	*mini_rt;

	mini_rt = (t_mini_rt *)param;
	clean_exit(mini_rt, SUCCESS);
	return (0);
}
