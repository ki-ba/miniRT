/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:24:56 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/19 15:01:14 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "objects.h"
#include <math.h>
#include "core.h"
#include "intersect.h"

double	intersect_cone(t_object *co, t_ray ray)
{
	(void)co;
	(void)ray;
	double		root = 0;

	return (root);
}

/**
	* @brief takes a ray and a sphere and determines where the to meet
	* @brief if they do.
	* @returns the value of t in the ray that intersects the sphere if it does,
	* @returns 0 otherwise.
*/
double	intersect_sphere(t_object *sp, t_ray ray)
{
	t_vec3		oc;
	double		a;
	double		b;
	double		c;
	double		root;

	oc.x = ray.ori.x - sp->center.x;
	oc.y = ray.ori.y - sp->center.y;
	oc.z = ray.ori.z - sp->center.z;
	a = vec3_dot(ray.dir, ray.dir);
	b = 2 * vec3_dot(ray.dir, oc);
	c = vec3_dot(oc, oc) - (sp->diam / 2) * (sp->diam / 2);
	if (resolve_eq2(a, b, c, &root))
		return (root);
	return (0);
}

static double	intersect_cylinder_caps(t_object *cy, t_ray ray, const double r, const bool tb)
{
	t_vec3	n_cap;
	t_vec3	c_cap;
	double 	root;
	double	denom;
	double	num;

	if (tb)
	{
		n_cap = cy->n;
		c_cap = vec3_add(cy->center, vec3_scale(cy->n, cy->h / 2));
	}
	else
	{
		n_cap = vec3_scale(cy->n, -1);
		c_cap = vec3_sub(cy->center, vec3_scale(cy->n, cy->h / 2));
	}
	denom = vec3_dot(ray.dir, n_cap);
	if (fabs(denom) < EPSILON)
		return (0);
	num = vec3_dot(vec3_sub(c_cap, ray.ori), n_cap);
	root = num / denom;
	if (root <= 0)
		return (0);
	t_vec3 p_cap = vec3_add(ray.ori, vec3_scale(ray.dir, root));
	t_vec3 v = vec3_sub(p_cap, c_cap);
	if (vec3_dot(v, v) <= r * r)
		return (root);
	return (0);
}

static double	intersect_cylinder_body(t_object *cy, t_ray ray, const double dir_norm, const double r)
{
	const t_vec3	oc = vec3_sub(ray.ori, cy->center);
	const double	oc_norm = vec3_dot(oc, cy->n);
	double	a;
	double	b;
	double	c;

	double root;
	root = 0;

	a = vec3_dot(ray.dir, ray.dir) - (dir_norm * dir_norm);
	b = 2 * (vec3_dot(oc, ray.dir) - dir_norm * oc_norm);
	c = vec3_dot(oc, oc) - (oc_norm * oc_norm) - (r * r);
	if (!resolve_eq2(a, b, c, &root))
		return (0);
	t_vec3	p = vec3_add(ray.ori, vec3_scale(ray.dir, root));
	double	h = fabs(vec3_dot(vec3_sub(p, cy->center), cy->n));
	if (h <= cy->h / 2)
		return (root);
	return (0);
}

double	intersect_cylinder(t_object *cy, t_ray ray)
{
	const double	dir_norm = vec3_dot(ray.dir, cy->n);
	const double	r = cy->diam / 2; // remove
	double			body_root;
	double			caps_root;
	double			root;

	caps_root = intersect_cylinder_caps(cy, ray,  r, TRUE);
	if (caps_root <= EPSILON)
	{
		caps_root = intersect_cylinder_caps(cy, ray,  r, FALSE);
	}
	else
	{
		root = intersect_cylinder_caps(cy, ray,  r, FALSE);
		if (root > EPSILON)
			caps_root = fmin(caps_root, root);
	}
	body_root = intersect_cylinder_body(cy, ray, dir_norm, r);
	if (body_root <= EPSILON || caps_root <= EPSILON)
		root = fmax(body_root, caps_root);
	else
		root = fmin(body_root, caps_root);
	return (root);
}

/**
	* @brief takes a ray and a plane and determines where the point where meet 
	* @brief if they do.
	* @returns the value of t in the ray that intersects the plane if it does,
	* @returns 0 otherwise.
*/
double	intersect_plane(t_object *pl, t_ray ray)
{
	double	denom;

	denom = vec3_dot(ray.dir, pl->n);
	if (fabs(denom) < EPSILON)
		return (0);
	return (vec3_dot(vec3_sub(pl->p, ray.ori), pl->n) / denom);
}

/**
	* @brief takes a ray as param and loops through every object
	* @brief to determine the nearest intersection.
	* @return the value of t where the ray intersects the object closest to it,
	* @return -1 if it doesn't intersect any.
*/
t_inter	check_intersect_obj(t_vector *objects, t_ray ray)
{
	double		t;
	size_t		i;
	double		(*f_i[4])(t_object *, t_ray);
	t_inter		inter;
	t_object	*cur_object;

	f_i[0] = intersect_sphere;
	f_i[1] = intersect_plane;
	f_i[2] = intersect_cylinder;
	f_i[3] = intersect_cone;
	i = 0;
	inter.t = INFINITY;
	while (i < objects->nb_elements)
	{
		cur_object = get_ith_obj(objects, i);
		t = f_i[cur_object->type](cur_object, ray);
		if (t > 0.0 && t < inter.t)
		{
			inter.t = t;
			inter.obj = cur_object;
		}
		++i;
	}
	if (inter.t < INFINITY)
		inter.p = vec3_add(ray.ori, vec3_scale(ray.dir, inter.t));
	return (inter);
}

int	is_in_shadow(t_vector *objects, t_light *light, t_vec3 point)
{
	t_ray	ray;
	double	dist_light;
	t_inter	shadow_hit;
	t_vec3	to_light;

	to_light = vec3_sub(light->ori, point);
	dist_light = vec3_magnitude(to_light);
	ray.ori = vec3_add(point, vec3_scale(vec3_normalize(to_light), 1e-4));
	ray.dir = vec3_normalize(to_light);
	shadow_hit = check_intersect_obj(objects, ray);
	if (shadow_hit.t > EPSILON && shadow_hit.t < dist_light)
		return (TRUE);
	return (FALSE);
}
