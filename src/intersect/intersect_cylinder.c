/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:26:18 by kbarru            #+#    #+#             */
/*   Updated: 2026/02/03 13:30:27 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"
#include <math.h>
#include "core.h"

#define N_CAP 0 // cap normal
#define C_CAP 1 // cap center
#define P_CAP 2 // point of intersection

#define T_CAP 1
#define BODY 2
#define B_CAP 3


static double	inter_cyl_caps(t_object *cy, t_ray ray,
		const double r, const bool tb)
{
	t_vec3	cap[3];
	t_vec3	v;
	double	fraction[2];
	double	root;

	cap[N_CAP] = vec3_scale(cy->n, -1);
	cap[C_CAP] = vec3_sub(cy->center, vec3_scale(cy->n, cy->h / 2));
	if (tb)
	{
		cap[N_CAP] = cy->n;
		cap[C_CAP] = vec3_add(cy->center, vec3_scale(cy->n, cy->h / 2));
	}
	fraction[1] = vec3_dot(ray.dir, cap[N_CAP]);
	if (fabs(fraction[1]) < EPSILON)
		return (0);
	fraction[0] = vec3_dot(vec3_sub(cap[C_CAP], ray.ori), cap[N_CAP]);
	root = fraction[0] / fraction[1];
	if (root <= 0)
		return (0);
	cap[P_CAP] = vec3_add(ray.ori, vec3_scale(ray.dir, root));
	v = vec3_sub(cap[P_CAP], cap[C_CAP]);
	if (vec3_dot(v, v) <= r * r)
		return (root);
	return (0);
}

static double	inter_cyl_body(t_object *cy, t_ray ray,
		const double dir_dot, const double r)
{
	const t_vec3	oc = vec3_sub(ray.ori, cy->center);
	const double	oc_dot = vec3_dot(oc, cy->n);
	double			numbers[3];
	t_vec3			p;
	double			root;

	root = 0;
	numbers[0] = vec3_dot(ray.dir, ray.dir) - (dir_dot * dir_dot);
	numbers[1] = 2 * (vec3_dot(oc, ray.dir) - dir_dot * oc_dot);
	numbers[2] = vec3_dot(oc, oc) - (oc_dot * oc_dot) - (r * r);
	if (!resolve_eq2(numbers[0], numbers[1], numbers[2], &root))
		return (0);
	p = vec3_add(ray.ori, vec3_scale(ray.dir, root));
	if (fabs(vec3_dot(vec3_sub(p, cy->center), cy->n)) <= cy->h / 2)
		return (root);
	return (0);
}

double	intersect_cylinder(t_object *cy, t_ray ray)
{
	const double	dir_dot = vec3_dot(ray.dir, cy->n);
	const double	r = cy->diam / 2;
	double			roots[4];
	int				i;

	roots[0] = INFINITY;
	roots[T_CAP] = inter_cyl_caps(cy, ray, r, TRUE);
	roots[BODY] = inter_cyl_body(cy, ray, dir_dot, r);
	roots[B_CAP] = inter_cyl_caps(cy, ray, r, FALSE);

	i = 1;
	while (i < 4)
	{
		if (roots[i] > EPSILON && roots[0] > roots[i])
			roots[0] = roots[i];
		++i;
	}

	if (roots[0] == roots[T_CAP])
		cy->cap = 1;
	else if (roots[0] == roots[B_CAP])
		cy->cap = -1;
	else
		cy->cap = 0;
	return (roots[0]);
}
