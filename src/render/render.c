/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:21:16 by abetemps          #+#    #+#             */
/*   Updated: 2026/01/17 11:24:16 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"
#include "miniRT.h"
#include "vec3.h"
#include "render.h"
#include "intersect.h"
#include "core.h"
#include "mlx.h"

/*
	* @brief defines a viewport in front of the camera at a distance of 1,
	* @brief then shoot equally spaced "rays" through the viewport to the scene
	* @brief every ray that intersects an object then a light is shown.
*/
void	shoot_rays(t_mini_rt *m_rt)
{
	const t_mlx		*mlx = &m_rt->mlx;
	int				rhw;
	t_inter			inter;
	t_ray			ray;
	int				i;

	if (is_set_bit(m_rt->mode.v, RENDER))
		m_rt->scale = HQ_SCALE;
	else
		m_rt->scale = LQ_SCALE;
	i = 0;
	rhw = (H / m_rt->scale) * (W  / m_rt->scale);
	ray = (t_ray){m_rt->cam.ori, (t_vec3){0}};
	init_vp(&m_rt->cam);
	while (i < rhw)
	{
		ray = create_ray(m_rt->cam, i, m_rt->scale);
		inter = check_intersect_obj(m_rt->objects, ray);
		draw_intersection(m_rt, &inter, i);
		++i;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}
