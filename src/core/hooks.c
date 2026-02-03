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
#include <math.h>
#include "hooks.h"
#include "vec3.h"
#include "render.h"
#include "core.h"

int	handle_mouse_move(int x, int y, void *param)
{
	static t_vec3	last_pos = {(double)W / 2, (double)H / 2, 0};
	const t_vec3	d_mouse = {x - last_pos.x, y - last_pos.y, 0};
	const t_vec3	d_rot = {-SENSIVITY * d_mouse.x, -SENSIVITY * d_mouse.y, 0};
	t_mini_rt		*mini_rt;
	t_scene			*scene;

	mini_rt = (t_mini_rt *)param;
	scene = &mini_rt->scene;
	if (!is_set_bit(mini_rt->mode.v, RENDER))
	{
		scene->cam.dir = vec3_normalize((t_vec3){
				cos(scene->cam.rot.y) * cos(scene->cam.rot.x),
				sin(scene->cam.rot.y),
				cos(scene->cam.rot.y) * sin(scene->cam.rot.x)});
		scene->cam.rot = vec3_add(scene->cam.rot, d_rot);
		render_scene(mini_rt);
		lock_mouse(mini_rt, &last_pos, x, y);
	}
	return (0);
}

int	handle_mouse_scroll(int mouse_event, int x, int y, void *param)
{
	t_mini_rt		*mini_rt;
	const double	step = 0.02;

	(void)x;
	(void)y;
	mini_rt = (t_mini_rt *)param;
	if (is_set_bit(mini_rt->mode.v, RENDER))
		return (0);
	if (mouse_event == ON_MOUSEDOWN)
	{
		if (rad_to_deg(mini_rt->scene.cam.fov - step) > MIN_FOV_DEG)
			mini_rt->scene.cam.fov -= step;
		render_scene(mini_rt);
	}
	else if (mouse_event == ON_MOUSEUP)
	{
		if (rad_to_deg(mini_rt->scene.cam.fov + step) < MAX_FOV_DEG)
			mini_rt->scene.cam.fov += step;
		render_scene(mini_rt);
	}
	return (0);
}

static int	handle_move_keypress(int keysym, void *param)
{
	const double	s = 2;
	t_camera		*cam;

	cam = &((t_mini_rt *)param)->scene.cam;
	if (keysym == K_UP)
		cam->ori = vec3_sub(cam->ori, vec3_scale(cam->up, s));
	else if (keysym == K_DOWN)
		cam->ori = vec3_add(cam->ori, vec3_scale(cam->up, s));
	else if (keysym == K_RIGHT)
		cam->ori = vec3_add(cam->ori, vec3_scale(cam->right, s));
	else if (keysym == K_LEFT)
		cam->ori = vec3_sub(cam->ori, vec3_scale(cam->right, s));
	else if (keysym == K_FORWARD)
		cam->ori = vec3_add(cam->ori, vec3_scale(cam->dir, s));
	else if (keysym == K_BACKWARD)
		cam->ori = vec3_sub(cam->ori, vec3_scale(cam->dir, s));
	else if (keysym == K_RESET)
	{
		cam->ori = (t_vec3){0, 0, 0};
		cam->dir = (t_vec3){0, 0, VP_DISTANCE};
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
	render_scene(mini_rt);
	return (0);
}

int	handle_window_close(void *param)
{
	t_mini_rt	*mini_rt;

	mini_rt = (t_mini_rt *)param;
	clean_exit(mini_rt, SUCCESS);
	return (0);
}
