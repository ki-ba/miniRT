/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:55:15 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/06 10:56:43 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/**
	* @brief takes a ray and a sphere and determines where the to meet if they do.
	* @returns the value of t in the ray that intersects the sphere if it does,
	* @returns -1 otherwise.
	* NOTE: is -1 advisable? What other value could mean no intersection?
*/
int	check_intersect_sphere(t_camera cam, t_sphere *sp, t_ray ray)
{
	t_point		oc;

	// printf("Checking intersection with sphere at center (%f, %f, %f) and diameter %f\n",
		// sp->center.x, sp->center.y, sp->center.z, sp->diameter);
	oc = cam.origin;
	if (get_solution(1, (double)(ray.x * oc.y + ray.y * oc.y + ray.z * oc.z),
		(double)(oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - 
				  (sp->diameter / 2) * 
				  (sp->diameter / 2))) > 0)
	{
		// printf("Ray intersects sphere!\n");
		return (1);
	}
	(void)sp;
	(void)ray;
	return (0);
}

/*
	* @brief defines a viewport in front of the camera at a distance of 1,
	* @brief then shoot equally spaced "rays" through the viewport to the scene
	* @brief . every ray that intersects an object then a light is shown.
*/
void	shoot_rays(t_mini_rt *mini_rt)
{
	double	x;
	double	y;
	t_point	*viewport;
	t_ray	vp_ray;
	double	t;	

	y = 0;
	viewport = ft_calloc(WIDTH * HEIGHT / tan(FOV / 2), sizeof(t_point));
	while (y < WIDTH)
	{
		x = 0;
		while (x < HEIGHT)
		{
			printf("Shooting ray through viewport point (%f, %f, %f)\n", x, y, (double)VP_DISTANCE);
			vp_ray = (t_ray){(t_point){mini_rt->camera.origin.x, mini_rt->camera.origin.y, mini_rt->camera.origin.z}, x, y, VP_DISTANCE};
			vp_ray = normalize_ray(vp_ray);
			t = check_intersect_obj(mini_rt, vp_ray);
			if (t > 0)
				my_mlx_pixel_put(mini_rt->mlx.img.img, vp_ray.x, vp_ray.y, determine_color(vec_to_point(vp_ray, t), mini_rt->lights, mini_rt->objects).trgb);
			x += fabs(2 * tan(FOV / 2));
		}
		y += fabs(2 * tan(FOV / 2));
	}
	free(viewport);
	printf("Viewport size: %f x %f\n", WIDTH / tan(FOV / 2), HEIGHT / tan(FOV / 2));
	mlx_destroy_image(mini_rt->mlx.mlx, mini_rt->mlx.img.img);
	printf("hello");
	mlx_put_image_to_window(mini_rt->mlx.mlx, mini_rt->mlx.win, mini_rt->mlx.img.img, 0, 0);
	printf("height / tan(FOV/2): %f\n", HEIGHT / tan(FOV / 2));
}

/**
	* @brief takes a ray as param and loops through every object
	* @brief to determine the nearest intersection.
	* @return the value of t where the ray intersects the object closest to it,
	* @return -1 if it doesn't intersect any.
*/
double	check_intersect_obj(t_mini_rt *mini_rt, t_ray ray)
{
	t_list	*shapes;
	double	nearest;
	void	*object;

	nearest = INFINITY;
	shapes = mini_rt->objects;
	while (shapes)
	{
		if (((t_shape *)shapes->content)->type == SPHERE)
		{

			object = get_inner_shape(shapes);
			nearest = fmin(nearest, check_intersect_sphere(mini_rt->camera, (t_sphere *)object, ray));
		}
		shapes = shapes->next;
	}
	printf("Nearest intersection at t = %f\n", nearest);
	return (nearest);
}

