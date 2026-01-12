/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:21:16 by abetemps          #+#    #+#             */
/*   Updated: 2026/01/12 15:45:53 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "miniRT.h"
#include "vec3.h"
#include <math.h>
#include "render.h"
#include "objects.h"
#include "core.h"
#include "mlx.h"

t_object	*get_ith_obj(t_vector *vector, size_t	index); //TODO: remove
t_light		*get_ith_light(t_vector *vector, size_t index);

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
	cur_object = NULL;
	while (i < mini_rt->objects->nb_elements)
	{
		cur_object = get_ith_obj(mini_rt->objects, i);
		inter.obj = cur_object;
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
		++i;
	}
	if (inter.t < INFINITY)
		inter.p = vec3_add(ray.ori, vec3_scale(ray.dir, inter.t));
	return (inter);
}

/**
	* @brief for every light, determine a vector from intersection to the light.
	* @brief If the vector finds any object, discard said light.
	* @brief It does not enlighten the intersection point.
**/
static t_color	get_color(t_ambient amb, t_inter inter, t_light *light)
{
	t_color	c;
	t_vec3	light_dir;
	t_vec3	surface_normal;
	double	ndotl;

	// Light dir is the vector from the intersection point to the light source
	// Surface normal is the normal vector at the intersection point
	// NdotL is the dot product of the surface normal and the light direction
	// It represents the cosine of the angle between the two vectors
	// We use fmax to ensure that NdotL is not negative
	// The resulting color is calculated by scaling the light color by NdotL
	// and multiplying it with the intersection color
	light_dir = (t_vec3){0};
	c = mul_color(scale_color(amb.c, amb.i), inter.c);

	light_dir = vec3_substract(light->ori, inter.p);
	light_dir = vec3_normalize(light_dir);

	surface_normal = vec3_substract(inter.p, inter.obj->center);
	surface_normal = vec3_normalize(surface_normal);

	ndotl = fmax(0, vec3_dot(surface_normal, light_dir));
	c = add_color(c, scale_color(scale_color(mul_color(inter.c, light->c), ndotl), light->i));
	return (c);
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
	* @brief every ray that intersects an object then a light is shown.
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
			temp_ray.ori = mini_rt->cam.ori;
			temp_ray.dir = vec3_normalize(vec3_substract(p, mini_rt->cam.ori));
			inter = check_intersect_obj(mini_rt, temp_ray);
			if (inter.t > 0 && inter.t != INFINITY)
				my_mlx_pixel_put(&mini_rt->mlx.img, x, y, get_color(mini_rt->amb, inter, get_ith_light(mini_rt->lights, 0)).trgb);
			else
				my_mlx_pixel_put(&mini_rt->mlx.img, x, y, 0);
			++x;
			// mlx_put_image_to_window(mini_rt->mlx.mlx, mini_rt->mlx.win, mini_rt->mlx.img.img, 0, 0);
		}
		++y;
	}
	mlx_put_image_to_window(mini_rt->mlx.mlx, mini_rt->mlx.win, mini_rt->mlx.img.img, 0, 0);
}
