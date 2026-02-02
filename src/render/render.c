/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:21:16 by abetemps          #+#    #+#             */
/*   Updated: 2026/01/21 10:40:09 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"
#include "miniRT.h"
#include "vec3.h"
#include "render.h"
#include "intersect.h"
#include "hooks.h"
#include "core.h"
#include "mlx.h"
#include "debug.h"

/*
	* @brief defines a viewport in front of the camera at a distance of 1,
	* @brief then shoot equally spaced "rays" through the viewport to the scene
	* @brief every ray that intersects an object then a light is shown.
*/
void	shoot_rays(t_mini_rt *m_rt)
{
	t_inter		inter;
	t_ray		ray;
	t_mlx		*mlx;
	size_t		i;
	size_t		rdim;

	if (is_set_bit(m_rt->mode.v, RENDER))
		m_rt->scale = HQ_SCALE;
	else
		m_rt->scale = LQ_SCALE;
	rdim = (W / m_rt->scale) * (H / m_rt->scale);
	mlx = &m_rt->mlx;
	ray = (t_ray){m_rt->scene.cam.ori, (t_vec3){0}};
	i = 0;
	init_vp(&m_rt->scene.cam);
	print_properties(*m_rt);
	while (i < rdim)
	{
		ray = create_ray(m_rt->scene.cam, i, m_rt->scale);
		// printf("%f %f %f\n", ray.dir.x, ray.dir.y, ray.dir.z);
		inter = check_intersect_obj(m_rt->scene.objects, ray);
		draw_intersection(m_rt, &inter, i);
		++i;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}
