/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:43:45 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/17 15:25:30 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "intersect.h"

static inline t_vec3	get_normal_sphere(t_inter inter)
{
	return (vec3_normalize(vec3_sub(inter.p, inter.obj->center)));
}

static inline t_vec3	get_normal_plane(t_inter inter)
{
	return (vec3_normalize(inter.obj->n));
}

static t_vec3	get_normal_cylinder(t_inter inter)
{
	const t_vec3	c = inter.obj->center;
	const t_vec3	v = vec3_normalize(inter.obj->n);
	double			t;
	t_vec3			axis_point;
	t_vec3			normal;

	if (inter.obj->cap == 0)
	{
		t = vec3_dot(vec3_sub(inter.p, c), v);
		axis_point = vec3_add(c, vec3_scale(v, t));
		normal = vec3_sub(inter.p, axis_point);
	}
	else
		normal = vec3_scale(v, inter.obj->cap);
	if (vec3_dot(normal, inter.ray.dir) > 0)
		normal = vec3_scale(normal, -1);
	return (vec3_normalize(normal));
}

// static t_vec3	get_normal_cone(t_inter inter)
// {
// 	const t_vec3	c = inter.obj->center;
// 	const t_vec3	v = vec3_normalize(inter.obj->n);
// 	double			t;
// 	t_vec3			axis_point;
// 	t_vec3			normal;
//
// 	if (inter.obj->cap == 0)
// 	{
// 		t = vec3_dot(vec3_sub(inter.p, c), v);
// 		axis_point = vec3_add(c, vec3_scale(v, t));
// 		normal = vec3_sub(inter.p, axis_point);
// 	}
// 	else
// 		normal = vec3_scale(v, inter.obj->cap);
// 	if (vec3_dot(normal, inter.ray.dir) > 0)
// 		normal = vec3_scale(normal, -1);
// 	return (vec3_normalize(normal));
// }

t_vec3	get_normal_at_intersection(t_inter inter)
{
	t_vec3 (*n[N_HITTABLE_TYPES])(t_inter);
	n[0] = get_normal_sphere;
	n[1] = get_normal_plane;
	n[2] = get_normal_cylinder;
	return (n[inter.obj->type](inter));
}
