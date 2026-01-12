/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:39:49 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/07 15:52:04 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vec3.h"
#include "render.h"
#include "core.h"
#include "mlx.h"

int	mouse_move(int x, int y, t_mini_rt *mini_rt)
{
	const t_vec3	mouse = {x, y, VP_DISTANCE};
	const double	cx = WIDTH / 2;
	const double	cy = HEIGHT / 2;
	static t_vec3	center = {cx, cy, 0};
	const double	sensivity = .02;
	const t_vec3	dir = vec3_scale(vec3_normalize(vec3_substract(mouse, center)), sensivity);


	// int x1, y1 = 0;
	// mlx_mouse_get_pos(mini_rt->mlx.mlx, mini_rt->mlx.win, &x1, &y1);
	// if (x1 > WIDTH)
	// 	mlx_mouse_move(mini_rt->mlx.mlx, mini_rt->mlx.win, 0, y1);
	// else if (x1 < 0)
	// 	mlx_mouse_move(mini_rt->mlx.mlx, mini_rt->mlx.win, WIDTH, y1);
	// else if (y1 > HEIGHT)
	// 	mlx_mouse_move(mini_rt->mlx.mlx, mini_rt->mlx.win, x1, 0);
	// else if (y1 < 0)
	// 	mlx_mouse_move(mini_rt->mlx.mlx, mini_rt->mlx.win, x1, HEIGHT);
	//
	// printf("x: %d | y: %d\n", x, y);
	// printf("center: x: %f | y: %f | z: %f\n", center.x, center.y, center.z);
	// printf("dir: x: %f | y: %f | z: %f\n", dir.x, dir.y, dir.z);

	mini_rt->cam.dir = vec3_add(mini_rt->cam.dir, dir);
	center = mouse;
	// printf("cam.dir: x: %f | y: %f | z: %f\n", mini_rt->cam.dir.x, mini_rt->cam.dir.y, mini_rt->cam.dir.z);

	shoot_rays(mini_rt);
	return (0);
}

int	handle_mouse(int mouse_event, int x, int y, t_mini_rt	*mini_rt)
{
	const double	step = 0.05;
	(void) x;
	(void) y;

	if (mouse_event == 4)
	{
		if (rad_to_deg(mini_rt->cam.fov - step) > 0)
			mini_rt->cam.fov -= step;
	}
	else if (mouse_event == 5)
	{
		if (rad_to_deg(mini_rt->cam.fov + step) < 180)
			mini_rt->cam.fov += step;
	}
	shoot_rays(mini_rt);
	return (0);
}

int	handle_keypress(int keysym, t_mini_rt *mini_rt)
{
	double step = 0.5;

	if (keysym == 65307 || keysym == 113)
		clean_exit(mini_rt, SUCCESS);
	else if (keysym == 119)
		mini_rt->cam.ori = vec3_substract(mini_rt->cam.ori, vec3_scale(mini_rt->cam.up, step));
	else if (keysym == 115)
		mini_rt->cam.ori = vec3_add(mini_rt->cam.ori, vec3_scale(mini_rt->cam.up, step));
	else if (keysym == 100)
		mini_rt->cam.ori = vec3_add(mini_rt->cam.ori, vec3_scale(mini_rt->cam.right, step));
	else if (keysym == 97)
		mini_rt->cam.ori = vec3_substract(mini_rt->cam.ori, vec3_scale(mini_rt->cam.right, step));
	else if (keysym == 99)
		mini_rt->cam.ori = vec3_add(mini_rt->cam.ori, vec3_scale(mini_rt->cam.dir, step));
	else if (keysym == 122)
		mini_rt->cam.ori = vec3_substract(mini_rt->cam.ori, vec3_scale(mini_rt->cam.dir, step));
	else if (keysym == 114)
	{
		mini_rt->cam.ori.x = 0;
		mini_rt->cam.ori.y = 0;
		mini_rt->cam.ori.z = 0;
		mini_rt->cam.dir.x = 0;
		mini_rt->cam.dir.y = 0;
		mini_rt->cam.dir.z = VP_DISTANCE;
	}
	// printf("Camera position: x=%f, y=%f, z=%f\n", mini_rt->cam.ori.x, mini_rt->cam.ori.y, mini_rt->cam.ori.z);
	shoot_rays(mini_rt);
	return (0);
}

/**
	* @brief Handles keypress events.
* @param keysym The key symbol of the pressed key.
* @param mini_rt Pointer to the miniRT structure.
* @return 0 on success.
* @note Exits the program if the Escape 65307 key / q 113 key is pressed.
*/
int	handle_window_close(t_mini_rt *mini_rt)
{
	clean_exit(mini_rt, SUCCESS);
	return (0);
}
