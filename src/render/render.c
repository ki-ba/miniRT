/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:21:16 by abetemps          #+#    #+#             */
/*   Updated: 2026/01/14 16:38:22 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vec3.h"
#include "debug.h"
#include <math.h>
#include "render.h"
#include "objects.h"
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
	t_inter		inter;
	t_ray		ray;
	t_mlx		*mlx;
	int			i;

	mlx = &m_rt->mlx;
	ray = (t_ray){m_rt->cam.ori, (t_vec3){0}};
	i = 0;
	init_vp(&m_rt->cam);
	while (i < H * W)
	{
		ray = create_ray(m_rt->cam, i);
		inter = check_intersect_obj(m_rt->objects, ray);
		draw_intersection(m_rt, &inter, i);
		++i;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}
