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

double	intersect_cone(t_object *co, t_ray ray)
{
	const t_vec3	tip = vec3_add(co->center, vec3_scale(co->n, co->h));
	const t_vec3	ot = vec3_sub(ray.ori, tip);
	const double	dn = vec3_dot(ray.dir, co->n);
	const double	otn = vec3_dot(ot, co->n);
	const double	k = (co->diam / 2) / co->h;
	const double	m = 1 + (k * k);
	t_vec3			p;
	t_vec3			v;
	double			h;
	double			numbers[3];
	double			root;

	root = 0;
	numbers[0] = vec3_dot(ray.dir, ray.dir) - m * (dn * dn);
	numbers[1] = 2 * (vec3_dot(ot, ray.dir) - m * (dn * otn));
	numbers[2] = vec3_dot(ot, ot) - m * (otn * otn);
	if (!resolve_eq2(numbers[0], numbers[1], numbers[2], &root))
		return (0);

	p = vec3_add(ray.ori, vec3_scale(ray.dir, root));
	v = vec3_sub(p, tip);
	h = vec3_dot(vec3_sub(p, co->center), co->n);
	if (h > EPSILON && h <= co->h)
		return (root);

	return (0);
}

