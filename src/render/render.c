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
void	shoot_rays(t_mini_rt *m_rt, const int h_ratio, const int w_ratio)
{
	t_inter		inter;
	t_ray		ray;
	int			dt[2];
	int			ind[2];

	ray = (t_ray){m_rt->scene.cam.ori, (t_vec3){0}};
	ind[0] = 0;
	while (ind[0] < h_ratio)
	{
		ind[1] = 0;
		dt[1] = ind[0] - (h_ratio >> 1);
		while (ind[1] < w_ratio)
		{
			dt[0] = ind[1] - (w_ratio >> 1);
			ray = create_ray(m_rt->scene.cam, dt[0], dt[1]);
			inter = check_intersect_obj(m_rt->scene.objects, ray);
			draw_intersection(m_rt, &inter, ind[0] * w_ratio + ind[1]);
			++ind[1];
		}
		++ind[0];
	}
}

void	render_scene(t_mini_rt *m_rt)
{
	t_mlx	*mlx;
	int		h_ratio;
	int		w_ratio;

	mlx = &m_rt->mlx;
	if (is_set_bit(m_rt->mode.v, RENDER))
		m_rt->scale = HQ_SCALE;
	else
		m_rt->scale = LQ_SCALE;
	h_ratio = H / m_rt->scale;
	w_ratio = W / m_rt->scale;
	init_vp(&m_rt->scene.cam, m_rt->scale);
	if (DEBUG)
		print_mini_rt(m_rt);
	shoot_rays(m_rt, h_ratio, w_ratio);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}
