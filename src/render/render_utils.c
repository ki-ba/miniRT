/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:21:37 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/14 16:39:04 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "intersect.h"
#include "render.h"
#include "core.h"
#include <math.h>
#include "miniRT.h"

void	draw_intersection(t_mini_rt *m_rt, t_inter *inter, int *i)
{
	t_color	c;
	t_light	*light;
	int		j;

	j = *i;
	light = get_ith_light(m_rt->lights, 0);
	if (inter->t > 0 && inter->t != INFINITY)
	{
		c = get_color(m_rt->objects, m_rt->amb, *inter, light);
		if (is_set_bit(m_rt->mode.v, RENDER))
			my_mlx_pixel_put(&m_rt->mlx.img, *i % W, *i / W, c.trgb);
		else
		{
			while (*i < j + LQ_STEP && *i % W < W && *i / W < H)
			{
				my_mlx_pixel_put(&m_rt->mlx.img, *i % W, *i / W, c.trgb);
				++(*i);
			}
			--(*i);
		}
	}
	else
		my_mlx_pixel_put(&m_rt->mlx.img, *i % W, *i / W, 0);
}

t_ray	create_ray(t_camera cam, int index)
{
	t_ray	ray;
	t_vec3	h_offset;
	t_vec3	v_offset;
	t_vec3	p;

	h_offset = vec3_scale(cam.vp.hrz, (index % W + 0.5) / W);
	v_offset = vec3_scale(cam.vp.vrt, ((double)index / W + 0.5) / H);
	p = vec3_add(vec3_add(cam.vp.lower_left, h_offset), v_offset);
	ray.ori = cam.ori;
	ray.dir = vec3_normalize(vec3_substract(p, cam.ori));
	return (ray);
}

/**
	* @brief for every light, determine a vector from intersection to the light.
	* @brief If the vector finds any object, discard said light.
	* @brief It does not enlighten the intersection point.
**/
t_color	get_color(t_vector *objects, t_ambient amb, t_inter inter, t_light *light)
{
	t_color	c;
	t_vec3	light_dir;
	t_vec3	surface_normal;
	t_ray	to_light;
	double	ndotl;

	light_dir = (t_vec3){0};
	c = mul_color(scale_color(amb.c, amb.i), inter.c);
	to_light.ori = inter.p;
	to_light.dir = vec3_substract(light->ori, inter.p);
	to_light.dir = vec3_normalize(to_light.dir);
	if (is_in_shadow(objects, light, inter.p))
		return (c);
	light_dir = vec3_substract(light->ori, inter.p);
	light_dir = vec3_normalize(light_dir);
	surface_normal = vec3_substract(inter.p, inter.obj->center);
	surface_normal = vec3_normalize(surface_normal);
	ndotl = fmax(0, vec3_dot(surface_normal, light_dir));
	c = add_color(c, scale_color(scale_color(mul_color(inter.c, light->c), ndotl), light->i));
	return (c);
}
