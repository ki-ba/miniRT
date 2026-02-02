/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:49:44 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/19 14:52:29 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "objects.h"
#include "vectors.h"
#include "debug.h"
#include "mlx.h"

void	destroy_mini_rt(t_mini_rt *mini_rt)
{
	clear_vector(&mini_rt->scene.objects);
	clear_vector(&mini_rt->scene.lights);
	if (mini_rt->mlx.img.img)
		mlx_destroy_image(mini_rt->mlx.mlx, mini_rt->mlx.img.img);
	if (mini_rt->mlx.win)
		mlx_destroy_window(mini_rt->mlx.mlx, mini_rt->mlx.win);
	if (mini_rt->mlx.mlx)
	{
		mlx_destroy_display(mini_rt->mlx.mlx);
		free(mini_rt->mlx.mlx);
	}
}

void	init_mini_rt(t_mini_rt *mini_rt)
{
	mini_rt->scale = HQ_SCALE;
	mini_rt->mlx.mlx = NULL;
	mini_rt->mlx.win = NULL;
	mini_rt->mlx.img = (t_data){0};
	mini_rt->mode = (t_hooks){1 << RENDER};
	mini_rt->scene.lights = create_vector(1, sizeof(t_light), NULL);
	mini_rt->scene.objects = create_vector(1, sizeof(t_object), NULL);
	mini_rt->scene.cam = (t_camera){0};
	mini_rt->scene.amb = (t_ambient){0};
}

void	print_mini_rt(t_mini_rt *mini_rt)
{
	print_properties(*mini_rt);
	print_item_lst(mini_rt->scene.objects);
	print_lights(mini_rt->scene.lights);
}

void	clean_exit(t_mini_rt *mini_rt, int exit_code)
{
	destroy_mini_rt(mini_rt);
	exit(exit_code);
}

void	init_vp(t_camera *cam)
{
	const double	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	t_viewport		*vp;

	vp = &(cam->vp);
	cam->wup = (t_vec3){0, 1, 0};
	if (fabs(vec3_dot(cam->dir, cam->wup)) > 0.999)
		cam->wup = (t_vec3){0, 0, 1};
	cam->right = vec3_normalize(vec3_cross(cam->dir, cam->wup));
	cam->up = vec3_normalize(vec3_cross(cam->right, cam->dir));
	vp->vp_width = 2 * tan(cam->fov / 2) * VP_DISTANCE;
	vp->vp_height = vp->vp_width / aspect_ratio;
	vp->hrz = vec3_scale(cam->right, vp->vp_width);
	vp->vrt = vec3_scale(cam->up, vp->vp_height);
	vp->lower_left = vec3_add((cam->ori), vec3_scale(cam->dir, VP_DISTANCE));
	vp->lower_left = vec3_sub(vp->lower_left, vec3_scale(vp->hrz, 0.5));
	vp->lower_left = vec3_add(vp->lower_left, vec3_scale(vp->vrt, 0.5));
}
