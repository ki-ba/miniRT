/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:21:37 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/17 11:23:42 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "intersect.h"
#include "render.h"
#include "core.h"
#include <math.h>
#include "miniRT.h"

void	draw_intersection(t_mini_rt *m_rt, t_inter *inter, int i)
{
	t_color	c;

	if (inter->t > 0 && inter->t != INFINITY)
	{
		c = get_color(m_rt->objects, m_rt->amb, *inter, m_rt->lights);
		draw_upscaled(&m_rt->mlx.img, i, c, m_rt->scale);
	}
	else
		draw_upscaled(&m_rt->mlx.img, i, (t_color){0}, m_rt->scale);
}

t_ray	create_ray(t_camera cam, int index, int scale)
{
	t_ray	ray;
	t_vec3	h_offset;
	t_vec3	v_offset;
	t_vec3	p;

    int render_width  = W / scale;
    int render_height = H / scale;

    int rx = index % render_width;
    int ry = index / render_width;

    double u = (rx + 0.5) / (double)render_width;
    double v = (ry + 0.5) / (double)render_height;

	h_offset = vec3_scale(cam.vp.hrz, u);
	v_offset = vec3_scale(cam.vp.vrt, v);
	p = vec3_add(vec3_add(cam.vp.lower_left, h_offset), v_offset);
	ray.ori = cam.ori;
	ray.dir = vec3_normalize(vec3_substract(p, cam.ori));
	return (ray);
}

t_color	get_diffuse_color(t_color obj_c, t_light *l, t_inter inter)
{
	double	ndotl;
	t_vec3	normal;
	t_vec3	light_dir;
	t_color	diffuse;

	diffuse.trgb = 0;
	light_dir = (t_vec3){0};
	normal = (t_vec3){0};
	light_dir = vec3_normalize(vec3_substract(l->ori, inter.p));
	normal = get_normal_at_intersection(inter);
	ndotl = fmax(0, vec3_dot(normal, light_dir));
	diffuse = scale_color(scale_color(mul_color(obj_c, l->c), ndotl), l->i);
	return (diffuse);
}

/**
	* @brief for every light, determine a vector from intersection to the light.
	* @brief If the vector finds any object, discard said light.
	* @brief It does not enlighten the intersection point.
**/
t_color	get_color(t_vector *obj, t_ambient amb, t_inter inter, t_vector *lights)
{
	t_color	c;
	t_light	*light;
	size_t	i;

	i = 0;
	c = mul_color(scale_color(amb.c, amb.i), inter.c);
	while (i < lights->nb_elements)
	{
		// printf("Light %zu/%zu\n", i + 1, lights->nb_elements);
		light = get_ith_light(lights, i);
		if (!is_in_shadow(obj, light, inter.p))
			c = add_color(get_diffuse_color(inter.c, light, inter), c);
		++i;
	}
	return (c);
}
