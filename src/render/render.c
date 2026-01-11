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
#include "debug.h"

/**
	* @brief takes a ray and a sphere and determines where the to meet if they do.
	* @returns the value of t in the ray that intersects the sphere if it does,
	* @returns -1 otherwise.
	* NOTE: is -1 advisable? What other value could mean no intersection?
*/
double	check_intersect_sphere(t_object *sp, t_ray ray)
{
	t_vec3		oc;
	double		a;
	double		b;
	double		c;

	oc.x = ray.origin.x - sp->center.x;
	oc.y = ray.origin.y - sp->center.y;
	oc.z = ray.origin.z - sp->center.z;
	a = vec3_dot(ray.dir, ray.dir);
	double half_b = vec3_dot(ray.dir, *(t_vec3 *)&oc);
	b = 2.0 * half_b;
	c = vec3_dot(*(t_vec3 *)&oc, *(t_vec3 *)&oc) - (sp->diameter/2) * (sp->diameter/2);
		double disc = b * b - 4 * a * c;
	if (disc < 0)
		return (0);
	double sqrtd = sqrt(disc);
	double t1 = (-half_b - sqrtd) / (2 * a);  // NEAREST
	double t2 = (-half_b + sqrtd) / (2 * a);  // FAR

	// Return nearest VALID hit (avoid self-intersection)
	if (t1 > 0.001)
		return (t1);
	if (t2 > 0.001)
		return (t2);
	return (0);
}

/**
	* @brief takes a ray as param and loops through every object
	* @brief to determine the nearest intersection.
	* @return the value of t where the ray intersects the object closest to it,
	* @return -1 if it doesn't intersect any.
*/
t_inter	check_intersect_obj(t_mini_rt *mini_rt, t_ray ray)
{
	t_inter		intersection = (t_inter){0};
	double		nearest;
	t_object	*cur_object;
	t_color		near_color = (t_color){0};

	nearest = INFINITY;
	while (shapes)
	{
		if (((t_shape *)shapes->content)->type == SPHERE)
		{
			double t = check_intersect_sphere((t_sphere *)cur_object, ray);
			if (t > 0 && t < nearest)
			{
				nearest = t;
				near_color = ((t_sphere *)cur_object)->c;
				//near_color = (t_color)2147483647U;
			}
		}
		shapes = shapes->next;
	}
	ray.dir = (vec3_scale(ray.dir, nearest));
	intersection.p = *(t_vec3*)&ray.dir;
	intersection.c = near_color;
	intersection.t = nearest;
	if (nearest > 0.0)
	{
		// printf("\033[0;32m");
		// printf("Nearest intersection (t: %f) is point (%f, %f, %f)\n", nearest, ray.dir.x, ray.dir.y, ray.dir.z);
		// printf("\033[0m");
	}
	return (intersection);
}

/**
	* @brief for a given point, shoots towards each light 
	* @brief and calculates the color of the point.
*/
t_color	determine_color(t_vec3 ip, t_color ic, t_list *lights, t_list *objects)
{
	/* for every light, determine a vector from intersection to the light.
		If the vector finds any object, discard said light.
		It does not enlighten the intersection point.*/
	(void)ip;
	(void)ic;
	(void)lights;
	(void)objects;
	return (ic);
}

/*
	* @brief defines a viewport in front of the camera at a distance of 1,
	* @brief then shoot equally spaced "rays" through the viewport to the scene
	* @brief . every ray that intersects an object then a light is shown.
*/
void	shoot_rays(t_mini_rt *mini_rt)
{
	t_inter	inter;
	t_ray	temp_ray;
	int	x;
	int	y;

	double	u;
	double	v;

	const t_vec3 hrz = vec3_scale(mini_rt->camera.right, mini_rt->camera.vp_width);
	const t_vec3 vrt = vec3_scale(mini_rt->camera.up, mini_rt->camera.vp_height);
	t_vec3 lower_left = vec3_add((*(t_vec3 *)&mini_rt->camera.origin), mini_rt->camera.dir);

	const t_vec3 half_hrz = vec3_scale(hrz, 0.5);
	const t_vec3 half_vrt = vec3_scale(vrt, 0.5);

	lower_left = vec3_substract(lower_left, half_hrz);
	lower_left = vec3_substract(lower_left, half_vrt);

	temp_ray = (t_ray) {mini_rt->camera.origin, (t_vec3) {0}};
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			u = (x + 0.5) / WIDTH;
			v = (y + 0.5) / HEIGHT;

			t_vec3 h_offset = vec3_scale(hrz, u);
			t_vec3 v_offset = vec3_scale(vrt, v);

			t_vec3 p = vec3_add(lower_left, h_offset);
			p = vec3_add(p, v_offset);

			temp_ray.origin = mini_rt->camera.origin;
			temp_ray.dir = vec3_substract(p, *(t_vec3 *)&mini_rt->camera.origin);
			temp_ray.dir = vec3_normalize(temp_ray.dir);

			inter = check_intersect_obj(mini_rt, temp_ray);
			// printf("inter(pixel[%d,%d]): %f\n", x, y, inter.t);
			if (inter.t > 0 && inter.t != INFINITY)
			{
				my_mlx_pixel_put(&mini_rt->mlx.img, x, y, determine_color(inter.p, inter.c, mini_rt->lights, mini_rt->objects).trgb);
			}
			else
			{
				my_mlx_pixel_put(&mini_rt->mlx.img, x, y, mini_rt->ambient_light.color.trgb);
			}
			++x;
			// mlx_put_image_to_window(mini_rt->mlx.mlx, mini_rt->mlx.win, mini_rt->mlx.img.img, 0, 0);
		}
		++y;
	}
	mlx_put_image_to_window(mini_rt->mlx.mlx, mini_rt->mlx.win, mini_rt->mlx.img.img, 0, 0);
}


