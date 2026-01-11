/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:21:16 by abetemps          #+#    #+#             */
/*   Updated: 2026/01/07 15:52:14 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include <math.h>
#include "render.h"
#include "core.h"
#include "mlx.h"

t_object	*get_ith_element(t_vector *vector, size_t	index); //TODO: remove

/**
	* @brief takes a ray and a sphere and determines where the to meet if they do.
	* @returns the value of t in the ray that intersects the sphere if it does,
	* @returns -1 otherwise.
	* NOTE: is -1 advisable? What other value could mean no intersection?
*/
static double	check_intersect_sphere(t_object *sp, t_ray ray)
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
/**
	* @brief takes a ray and a plane and determines where the point where meet if they do.
	* @returns the value of t in the ray that intersects the plane if it does,
	* @returns -1 otherwise.
	* NOTE: is -1 advisable? What other value could mean no intersection?
*/
static inline double	check_intersect_plane(t_object *pl, t_ray ray)
{
	return (vec3_dot(vec3_substract(*(t_vec3 *)&pl->p, *(t_vec3 *)&ray.ori), pl->n) / vec3_dot(ray.dir, pl->n));
}

/**
	* @brief takes a ray and a cylinder and determines where the point where meet if they do.
	* @returns the value of t in the ray that intersects the cylinder if it does,
	* @returns -1 otherwise.
	* NOTE: is -1 advisable? What other value could mean no intersection?
*/
static inline double	check_intersect_cylinder(t_object *cy, t_ray ray)
{
	double	root;
	double	a = 0;//1 - (Ca • Rd)^2)Hd^2;
	double	b = 0;//2((Rd • Rl) - (Ca • Rd)(Ca • Rl));
	double	c = 0;//(Rl • Rl) - (Ca • Rl)^2 - Cr^2;

	a = 1 - vec3_dot(ray.dir, cy->n) * vec3_dot(ray.dir, cy->n);
	b = (2 * vec3_dot(ray.dir, vec3_substract(ray.ori, cy->center))) - (vec3_dot(ray.dir, cy->n) * vec3_dot(cy->n, vec3_substract(ray.ori, cy->center)));
	c = vec3_dot(vec3_substract(ray.ori, cy->center), vec3_substract(ray.ori, cy->center)) - (vec3_dot(cy->n, vec3_substract(ray.ori, cy->center)) * vec3_dot(cy->n, vec3_substract(ray.ori, cy->center))) - cy->diam / 2;
	if (resolve_eq2(a, b, c, &root))
		return (root);
	return (0);
}

/**
	* @brief takes a ray as param and loops through every object
	* @brief to determine the nearest intersection.
	* @return the value of t where the ray intersects the object closest to it,
	* @return -1 if it doesn't intersect any.
*/
static t_inter	check_intersect_obj(t_mini_rt *mini_rt, t_ray ray)
{
	t_inter		inter;
	t_object	*cur_object;
	double		t;
	size_t		i;

	i = 0;
	inter = (t_inter){0};
	inter.t = INFINITY;
	while (i < mini_rt->objects->nb_elements)
	{
		cur_object = get_ith_element(mini_rt->objects, i);
		if (cur_object->type == SPHERE)
		{
			t = check_intersect_sphere(cur_object, ray);
			if (t > 0.0 && t < inter.t)
			{
				inter.t = t;
				inter.c = (cur_object)->c;
			}
		}
		else if (cur_object->type == PLANE)
		{
			t = check_intersect_plane(cur_object, ray);
			if (t > 0.0 && t < inter.t)
			{
				inter.t = t;
				inter.c = (cur_object)->c;
			}
		}
		else if (cur_object->type == CYLINDER)
		{
			t = check_intersect_cylinder(cur_object, ray);
			if (t > 0.0 && t < inter.t)
			{
				inter.t = t;
				inter.c = (cur_object)->c;
			}
		}
		++i;
	}
	if (inter.t < INFINITY)
		inter.p = vec3_add(ray.ori, vec3_scale(ray.dir, inter.t));
	return (inter);
}

/**
	* @brief for every light, determine a vector from intersection to the light.
	* @brief If the vector finds any object, discard said light.
	* @brief It does not enlighten the intersection point.*/

static t_color	get_color(t_vec3 ip, t_color ic, t_vector *lights, t_vector *objects)
{
	(void)ip;
	(void)ic;
	(void)lights;
	(void)objects;
	return (ic);
}

static void	init_vp(t_viewport *vp, t_camera *cam)
{
	vp->hrz = vec3_scale(cam->right, cam->vp_width);
	vp->vrt = vec3_scale(cam->up, cam->vp_height);
	vp->lower_left = vec3_add((cam->ori), cam->dir);
	vp->lower_left = vec3_substract(vp->lower_left, vec3_scale(vp->hrz, 0.5));
	vp->lower_left = vec3_substract(vp->lower_left, vec3_scale(vp->vrt, 0.5));
}

/*
	* @brief defines a viewport in front of the camera at a distance of 1,
	* @brief then shoot equally spaced "rays" through the viewport to the scene
	* @brief . every ray that intersects an object then a light is shown.
*/
void	shoot_rays(t_mini_rt *mini_rt)
{
	t_viewport	vp;
	t_inter		inter;
	t_ray		temp_ray;
	t_vec3		h_offset;
	t_vec3		v_offset;
	t_vec3		p;
	int			x;
	int			y;

	temp_ray = (t_ray){mini_rt->cam.ori, (t_vec3){0}};
	y = 0;
	init_vp(&vp, &mini_rt->cam);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			h_offset = vec3_scale(vp.hrz, (x + 0.5) / WIDTH);
			v_offset = vec3_scale(vp.vrt, (y + 0.5) / HEIGHT);
			p = vec3_add(vec3_add(vp.lower_left, h_offset), v_offset);
			temp_ray.ori= mini_rt->cam.ori;
			temp_ray.dir = vec3_normalize(vec3_substract(p, mini_rt->cam.ori));
			inter = check_intersect_obj(mini_rt, temp_ray);
			if (inter.t > 0 && inter.t != INFINITY)
				my_mlx_pixel_put(&mini_rt->mlx.img, x, y, get_color(inter.p, inter.c, mini_rt->lights, mini_rt->objects).trgb);
			else
				my_mlx_pixel_put(&mini_rt->mlx.img, x, y, mini_rt->amb.c.trgb);
			++x;
			// mlx_put_image_to_window(mini_rt->mlx.mlx, mini_rt->mlx.win, mini_rt->mlx.img.img, 0, 0);
		}
		++y;
	}
	mlx_put_image_to_window(mini_rt->mlx.mlx, mini_rt->mlx.win, mini_rt->mlx.img.img, 0, 0);
}
