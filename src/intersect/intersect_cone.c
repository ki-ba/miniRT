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

#define CAP 1
#define BODY 2

static double	inter_cone_cap(t_object *co, t_ray ray,
		const double r)
{
	t_vec3	cap[3];
	t_vec3	v;
	double	fraction[2];
	double	root;

	cap[N_CAP] = vec3_scale(co->n, -1);
	cap[C_CAP] = co->center;
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

static double inter_cone_body(t_object *co, t_ray ray)
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

double	intersect_cone(t_object *co, t_ray ray)
{
	const double	r = co->diam / 2;
	double			roots[3];
	int				i;

	roots[0] = INFINITY;
	roots[CAP] = inter_cone_cap(co, ray, r);
	roots[BODY] = inter_cone_body(co, ray);
	i = 1;
	while (i < 3)
	{
		if (roots[i] > EPSILON && roots[0] > roots[i])
			roots[0] = roots[i];
		++i;
	}
	if (roots[0] == roots[CAP])
		co->cap = -1;
	else
		co->cap = 0;
	return (roots[0]);
}

