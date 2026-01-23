/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:39:49 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/17 11:52:15 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysymdef.h>
#include <math.h>
#include "mlx.h"
#include "hooks.h"
#include "vec3.h"
#include "render.h"
#include "core.h"
#include "debug.h"

extern inline t_bool is_set_bit(unsigned int v, unsigned int flag)
{
	return ((v >> flag) == 1);
}

static void	handle_hook_mode(t_mini_rt *mrt, int keysym)
{
	const char ctrls[HOOKS_MODE_QTY] = {K_RENDER, K_OBJ};
	int	i;

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
	// printf("mode: ");
	// print_binary(mrt->mode.v);
	// printf("\n");
}

void	lock_mouse(t_mini_rt *mrt, t_vec3 *pos, int x, int y)
{
	*pos = (t_vec3) {x, y, 0};
	if (x > (W - (W * DEADZONE)))
	{
		mlx_mouse_move(mrt->mlx.mlx, mrt->mlx.win, 1 + (W * DEADZONE), y);
		*pos = (t_vec3) {1 + (W * DEADZONE), y, 0};
	}
	else if (x < (0 + (W * DEADZONE)))
	{
		mlx_mouse_move(mrt->mlx.mlx, mrt->mlx.win, W - (W * DEADZONE), y);
		*pos = (t_vec3) {W - (W * DEADZONE), y, 0};
	}
	if (y > (H - (H * DEADZONE)))
	{
		mlx_mouse_move(mrt->mlx.mlx, mrt->mlx.win, x, 1 + (H * DEADZONE));
		*pos = (t_vec3) {x, 1 + (H * DEADZONE), 0};
	}
	else if (y < (0 + (H * DEADZONE)))
	{
		mlx_mouse_move(mrt->mlx.mlx, mrt->mlx.win, x, H - (H * DEADZONE));
		*pos = (t_vec3) {x, H - (H * DEADZONE), 0};
	}

}

int handle_mouse_move(int x, int y, void *param)
{
	static t_vec3	last_pos = {W / 2, H / 2, 0};
	const t_vec3	mouse_delta = {x - last_pos.x, y - last_pos.y, 0};
	const t_vec3	rotation_delta = {-SENSIVITY * mouse_delta.x, SENSIVITY * mouse_delta.y, 0};
	t_mini_rt		*mini_rt;

	mini_rt = (t_mini_rt *)param;
	if (!is_set_bit(mini_rt->mode.v, RENDER))
	{
		mini_rt->cam.dir = vec3_normalize((t_vec3) {
				cos(mini_rt->cam.rot.y) * cos(mini_rt->cam.rot.x),
				sin(mini_rt->cam.rot.y),
				cos(mini_rt->cam.rot.y) * sin(mini_rt->cam.rot.x)});
		mini_rt->cam.rot = vec3_add(mini_rt->cam.rot, rotation_delta);
		shoot_rays(mini_rt);
		lock_mouse(mini_rt, &last_pos, x, y);
	}
	return (0);
}

int	handle_mouse_scroll(int mouse_event, int x, int y, void *param)
{
	const double	step = 0.02;
	t_mini_rt		*mini_rt;
	(void) x;
	(void) y;
	
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

static int handle_move_keypress(int keysym, void *param)
{
	t_mini_rt *mini_rt;
	const double step = 2;

	mini_rt = (t_mini_rt *)param;

	if (keysym == K_UP)
		mini_rt->cam.ori = vec3_substract(mini_rt->cam.ori, vec3_scale(mini_rt->cam.up, step));
	else if (keysym == K_DOWN)
		mini_rt->cam.ori = vec3_add(mini_rt->cam.ori, vec3_scale(mini_rt->cam.up, step));
	else if (keysym == K_RIGHT)
		mini_rt->cam.ori = vec3_add(mini_rt->cam.ori, vec3_scale(mini_rt->cam.right, step));
	else if (keysym == K_LEFT)
		mini_rt->cam.ori = vec3_substract(mini_rt->cam.ori, vec3_scale(mini_rt->cam.right, step));
	else if (keysym == K_FORWARD)
		mini_rt->cam.ori = vec3_add(mini_rt->cam.ori, vec3_scale(mini_rt->cam.dir, step));
	else if (keysym == K_BACKWARD)
		mini_rt->cam.ori = vec3_substract(mini_rt->cam.ori, vec3_scale(mini_rt->cam.dir, step));
	else if (keysym == K_RESET)
	{
		mini_rt->cam.ori.x = 0;
		mini_rt->cam.ori.y = 0;
		mini_rt->cam.ori.z = 0;
		mini_rt->cam.dir.x = 0;
		mini_rt->cam.dir.y = 0;
		mini_rt->cam.dir.z = VP_DISTANCE;
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
	t_mini_rt *mini_rt;

	mini_rt = (t_mini_rt *)param;

	handle_hook_mode(mini_rt, keysym);
	// printf("Key pressed: %d\n", keysym);
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
	t_mini_rt *mini_rt;

	mini_rt = (t_mini_rt *)param;
	clean_exit(mini_rt, SUCCESS);
	return (0);
}
