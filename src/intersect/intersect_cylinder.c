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

double	inter_cyl_caps(t_object *cy, t_ray ray, const double r, const bool tb)
{
	t_vec3	cap[3];
	t_vec3	v;
	double	fraction[2];
	double	root;

	return (0);
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

/**	@brief puts both roots of the equation into root[0] and root[1]
 *	@brief in ascending order.
**/
t_bool	cyl_resolve_eq2(double a, double b, double c, double root[2])
{
	double	discriminant;
	double	temp[2];

	root[0] = 0;
	root[1] = 0;
	if (!root || a == 0)
		return (FALSE);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (FALSE);
	else
	{
		temp[0] = (-b - sqrt(discriminant)) / (2 * a);
		temp[1] = (-b + sqrt(discriminant)) / (2 * a);
	}
	root[0] = fmin(temp[0], temp[1]);
	root[1] = fmax(temp[0], temp[1]);
	return (TRUE);
}

double	define_root(t_ray ray, t_object *cy, double roots[2])
{
	size_t	i;
	t_vec3	p;

	i = 0;
	while (i < 2)
	{
		if (roots[i] > EPSILON)
		{
			p = vec3_add(ray.ori, vec3_scale(ray.dir, roots[i]));
			if (fabs(vec3_dot(vec3_sub(p, cy->center), cy->n)) <= cy->h / 2)
				return (roots[i]);
		}
		++i;
	}
	return (0);
}

double	inter_cyl_body(t_object *cy, t_ray ray, double dir_norm, double r)
{
	const t_vec3	oc = vec3_sub(ray.ori, cy->center);
	const double	oc_norm = vec3_dot(oc, cy->n);
	double			numbers[3];
	double			root[2];

	numbers[0] = vec3_dot(ray.dir, ray.dir) - (dir_norm * dir_norm);
	numbers[1] = 2 * (vec3_dot(oc, ray.dir) - dir_norm * oc_norm);
	numbers[2] = vec3_dot(oc, oc) - (oc_norm * oc_norm) - (r * r);
	if (!cyl_resolve_eq2(numbers[0], numbers[1], numbers[2], root))
		return (0);
	return (define_root(ray, cy, root));
}

double	intersect_cylinder(t_object *cy, t_ray ray)
{
	const double	dir_norm = vec3_dot(ray.dir, cy->n);
	double			body_root;
	double			caps_root;
	double			root;

	caps_root = inter_cyl_caps(cy, ray, cy->diam / 2, TRUE);
	if (caps_root <= EPSILON)
		caps_root = inter_cyl_caps(cy, ray, cy->diam / 2, FALSE);
	else
	{
		root = inter_cyl_caps(cy, ray, cy->diam / 2, FALSE);
		if (root > EPSILON)
			caps_root = fmin(caps_root, root);
	}
	body_root = inter_cyl_body(cy, ray, dir_norm, cy->diam / 2);
	if (body_root <= EPSILON || caps_root <= EPSILON)
		root = fmax(body_root, caps_root);
	else
		root = fmin(body_root, caps_root);
	return (root);
}
