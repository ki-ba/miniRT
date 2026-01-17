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

t_vec3	get_normal_sphere(t_inter inter)
{
	t_vec3	normal;

	normal = vec3_sub(inter.p, inter.obj->center);
	return (vec3_normalize(normal));
}

t_vec3	get_normal_plane(t_inter inter)
{
	return (vec3_normalize(inter.obj->n));
}

t_vec3	get_normal_cylinder(t_inter inter)
{
	(void)inter;
	return ((t_vec3){0});
}

t_vec3	get_normal_at_intersection(t_inter inter)
{
	t_vec3	normal;

	t_vec3 (*n[3])(t_inter);
	(void)normal;
	n[0] = get_normal_sphere;
	n[1] = get_normal_plane;
	n[2] = get_normal_cylinder;
	return (n[inter.obj->type](inter));
}
