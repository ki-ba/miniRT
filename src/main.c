/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:04:24 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/07 14:50:00 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "core.h"
#include "render.h"
#include "mlx.h"
#include "vectors.h"

#include <fcntl.h>

t_object	*get_ith_element(t_vector *vector, size_t	index); //TODO: remove

void	set_vec3_color(t_mini_rt *mini_rt, t_vec3 vp_point)
{
	t_vec3	ray;

	ray.x = vp_point.x - mini_rt->camera.origin.x;
	ray.y = vp_point.y - mini_rt->camera.origin.y;
	ray.z = vp_point.z - mini_rt->camera.origin.z;
}

/**
	* @brief takes a ray and a sphere and determines where the to meet if they do.
	* @returns the value of t in the ray that intersects the sphere if it does,
	* @returns -1 otherwise.
	* NOTE: is -1 advisable? What other value could mean no intersection?
*/
int	check_intersect_sphere(t_camera cam, t_object *sp, t_ray ray)
{
	t_vec3		oc;
	double		b;
	double		c;
	double		root;

	root = 0;
	oc = cam.origin;
	b = 2 * (double)(ray.dir.x * (oc.x - sp->center.x)+ ray.dir.y *(oc.y - sp->center.y)  + ray.dir.z *(oc.z - sp->center.z));
	c = (double)((oc.x - sp->center.x)*(oc.x - sp->center.x) + (oc.y - sp->center.y)*(oc.y - sp->center.y) + (oc.z - sp->center.z)*(oc.z - sp->center.z)- (sp->diameter / 2) * (sp->diameter / 2));
	// printf("Checking intersection of ray (%f, %f, %f)\n", ray.dir.x, ray.dir.y, ray.dir.z);
	if (resolve_eq2(1,b,c, &root) == TRUE)
	{
		// Print in GREEN in terminal if found
		// printf("\033[0;32m");
		// printf("Intersection at t = %f\n", root);
		// printf("\033[0m");
		return (root);
	}
	// Print in RED in terminal if not found
	// printf("\033[0;31mNo intersection with ray at direction (%f, %f, %f)\033[0m\n",
	// 	ray.dir.x, ray.dir.y, ray.dir.z);
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
	t_inter		intersection;
	double		nearest;
	t_object	*cur_object;
	t_color		near_color;
	size_t		i;

	nearest = INFINITY;
	i = 0;
	while (i < mini_rt->objects->nb_elements)
	{
		cur_object = get_ith_element(mini_rt->objects, i);
		if (cur_object->type == SPHERE)
		{
			nearest = fmin(nearest, check_intersect_sphere(mini_rt->camera, cur_object, ray));
			near_color = (cur_object)->color;
		}
		++i;
	}
	ray.dir = (vec3_scale(&ray.dir, nearest));
	intersection.t = nearest;
	intersection.p = *(t_vec3 *)&ray.dir;
	return (intersection);
}

/**
	* @brief for a given point, shoots towards each light 
	* @brief and calculates the color of the point.
*/
t_color	determine_color(t_vec3 ip, t_color ic, t_vector *lights, t_vector *objects)
{
	/* for every light, determine a vector from intersection to the light.
		If the vector finds any object, discard said light.
		It does not enlighten the intersection point.*/
	(void)ip;
	(void)ic;
	(void)lights;
	(void)objects;
	return ((t_color)(uint32_t)255);
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
	t_inter	inter;
	t_ray	temp_ray;

	y = 0;
	while (y < WIDTH)
	{
		x = 0;
		while (x < HEIGHT)
		{
			temp_ray = (t_ray){0}; // Determine vect3 for this ray.
			inter = check_intersect_obj(mini_rt, temp_ray);
			if (inter.t > 0)
			{
				my_mlx_pixel_put(&mini_rt->mlx.img, x, y, determine_color(inter.p, inter.c, mini_rt->lights, mini_rt->objects).trgb);
			}
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(mini_rt->mlx.mlx, mini_rt->mlx.win, mini_rt->mlx.img.img, 0, 0);
}

int	check_properties(t_mini_rt *mini_rt)
{
	if (!mini_rt->camera.is_defined || !mini_rt->ambient_light.is_defined)
	{
		write(2, MISSING_PROPERTY_MSG, ft_strlen(MISSING_PROPERTY_MSG));
		return (GENERIC_ERR);
	}
	if (mini_rt->lights->nb_elements > 1)
	{
		write(2, TOO_MUCH_ELEMENTS_MSG, ft_strlen(TOO_MUCH_ELEMENTS_MSG));
		return (GENERIC_ERR);
	}
	return (0);
}

int	main(int argc, char *argv[])

{
	t_mini_rt	mini_rt;
	int			fd;

	init_mini_rt(&mini_rt);
	if (argc != 2 || !check_extension(argv[1], EXTENSION))
	{
		write(2, USAGE_ERR_MSG, ft_strlen(USAGE_ERR_MSG));
		clean_exit(&mini_rt, GENERIC_ERR);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (write(2, FILE_ERR_MSG, ft_strlen(FILE_ERR_MSG)));
	if (parse_items_in_file(&mini_rt, fd))
		clean_exit(&mini_rt, GENERIC_ERR);
	if (check_properties(&mini_rt))
		clean_exit(&mini_rt, GENERIC_ERR);
	ft_init_mlx(&mini_rt);
	print_mini_rt(&mini_rt);
	shoot_rays(&mini_rt);
	mlx_loop(mini_rt.mlx.mlx);
	destroy_mini_rt(&mini_rt);
	return (0);
}
