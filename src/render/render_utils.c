/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:21:37 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/21 10:40:34 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "intersect.h"
#include "render.h"
#include "core.h"
#include <math.h>
#include "miniRT.h"
#include "vec3.h"

void	draw_intersection(t_mini_rt *m_rt, t_inter *inter, int i)
{
	t_color	c;

	if (inter->t > 0 && inter->t != INFINITY)
	{
		c = get_color(*inter, &m_rt->scene);
		draw_upscaled(&m_rt->mlx.img, i, c, m_rt->scale);
	}
	else
		draw_upscaled(&m_rt->mlx.img, i, (t_color){0}, m_rt->scale);
}

t_ray	create_ray(t_camera cam, int i, int scale)
{
	t_ray	ray;
	t_vec3	d_h;
	t_vec3	d_v;
	t_vec3	p;

	d_h = vec3_scale(cam.vp.hrz, (i % (W / scale) + 0.5) / (W / scale));
	d_v = vec3_scale(cam.vp.vrt, (i / (W / scale) + 0.5) / (H / scale));
	p = vec3_sub(vec3_add(cam.vp.lower_left, d_h), d_v);
	ray.ori = cam.ori;
	ray.dir = vec3_normalize(vec3_sub(p, cam.ori));
	return (ray);
}

t_color	get_diffuse_color(t_light *l, t_inter inter, t_vec3 normal)
{
	double	ndotl;
	t_vec3	light_dir;
	t_color	diffuse;
	t_color	obj_c;

	obj_c = inter.obj->c;
	diffuse.trgb = 0;
	light_dir = vec3_normalize(vec3_sub(l->ori, inter.p));
	ndotl = fmax(0, vec3_dot(normal, light_dir));
	diffuse = scale_color(scale_color(mul_color(obj_c, l->c), ndotl), l->i);
	return (diffuse);
}

t_color	get_specular_color(t_light *l, t_inter inter, t_camera cam, t_vec3 normal)
{
	t_vec3	light_dir;
	t_vec3	view_dir;
	t_vec3	r_v;
	double	s_f;

	normal = get_normal_at_intersection(inter);
	view_dir = vec3_normalize(vec3_sub(cam.ori, inter.p));
	light_dir = vec3_normalize(vec3_sub(l->ori, inter.p));
	r_v = vec3_scale(normal, vec3_dot(normal, light_dir));
	r_v = vec3_sub(vec3_scale(r_v, 2), light_dir);
	r_v = vec3_normalize(r_v);
	s_f = pow(fmax(0, vec3_dot(r_v, view_dir)), SHININESS);
	return (scale_color(l->c, s_f * l->i));
}

/**
	* @brief for every light, determine a vector from intersection to the light.
	* @brief If the vector finds any object, discard said light.
	* @brief It does not enlighten the intersection point.
**/
t_color	get_color(t_inter inter, t_scene *scene)
{
	t_color	c;
	t_light	*light;
	t_vec3	view_dir;
	t_vec3	normal;
	size_t	i;

	view_dir = vec3_normalize(vec3_sub(scene->cam.ori, inter.p));
	normal = get_normal_at_intersection(inter);
	if (vec3_dot(normal, view_dir) < 0)
		normal = vec3_scale(normal, -1);
	i = -1;
	c = mul_color(scale_color(scene->amb.c, scene->amb.i), inter.obj->c);
	while (++i < scene->lights->nb_elements)
	{
		light = get_ith_light(scene->lights, i);
		if (is_in_shadow(scene->objects, light, inter.p))
			continue ;
		c = add_color(get_diffuse_color(light, inter, normal), c);
		c = add_color(get_specular_color(light, inter, scene->cam, normal), c);
	}
	return (c);
}
