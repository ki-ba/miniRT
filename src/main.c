/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:04:24 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/06 11:37:55 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "parsing.h"
#include "miniRT.h"
#include "libft.h"
#include "core.h"
#include "math.h"
#include "vec3.h"

#include <math.h>
#include <fcntl.h>

/**
	* @brief takes a ray and a sphere and determines where the to meet if they do.
	* @returns the value of t in the ray that intersects the sphere if it does,
	* @returns -1 otherwise.
	* NOTE: is -1 advisable? What other value could mean no intersection?
*/
double	check_intersect_sphere(t_camera cam, t_sphere *sp, t_ray ray)
{
	t_point		oc;
	double		a;
	double		b;
	double		c;
	double		root;

	root = 0;
	oc.x = sp->center.x - cam.origin.x;
	oc.y = sp->center.y - cam.origin.y;
	oc.z = sp->center.z - cam.origin.z;

	a = vec3_dot(&ray.dir, &ray.dir);
	double half_b = vec3_dot(&ray.dir, (t_vec3 *)&oc);
	b = 2.0 * half_b;
	c = vec3_dot((t_vec3 *)&oc, (t_vec3 *)&oc) - (sp->diameter/2) * (sp->diameter/2);
	double disc = b * b - 4 * a * c;
	
	if (disc < 0)
		return (0);
	double sqrtd = sqrt(disc);
    double t1 = (-b - sqrtd) / (2 * a);  // NEAREST
    double t2 = (-b + sqrtd) / (2 * a);  // FAR
    
    // Return nearest VALID hit (avoid self-intersection)
    if (t1 > 0.001)
        return (t1);
    if (t2 > 0.001)
        return (t2);
    return (0);
	// printf("Checking intersection of ray (%f, %f, %f)\n", ray.dir.x, ray.dir.y, ray.dir.z);
	// if (resolve_eq2(1,b,c, &root) == TRUE)
	// {
	// 	// Print in GREEN in terminal if found
	// 	// printf("\033[0;32m");
	// 	// printf("Intersection at t = %f\n", root);
	// 	// printf("\033[0m");
	// 	return (root);
	// }
	// // Print in RED in terminal if not found
	// // printf("\033[0;31mNo intersection with ray at direction (%f, %f, %f)\033[0m\n",
	// // 	ray.dir.x, ray.dir.y, ray.dir.z);
	// return (0);
}

void	*get_inner_shape(t_list *shape)
{
	if (!shape)
		return (NULL);
	if (!shape->content)
		return (NULL);
	if (!((t_shape *)shape->content)->shape)
		return (NULL);
	return (((t_shape *)shape->content)->shape);
}

/**
	* @brief takes a ray as param and loops through every object
	* @brief to determine the nearest intersection.
	* @return the value of t where the ray intersects the object closest to it,
	* @return -1 if it doesn't intersect any.
*/
t_inter	check_intersect_obj(t_mini_rt *mini_rt, t_ray ray)
{
	t_list	*shapes;
	t_inter	intersection = (t_inter){0};
	double	nearest;
	void	*cur_object;
	t_color	near_color = (t_color){0};

	nearest = INFINITY;
	shapes = mini_rt->objects;
	while (shapes)
	{
		cur_object = get_inner_shape(shapes);
		if (((t_shape *)shapes->content)->type == SPHERE)
		{
			double t = check_intersect_sphere(mini_rt->camera, (t_sphere *)cur_object, ray);
			if (t > 0 && t < nearest)
			{
				nearest = t;
				near_color = ((t_sphere *)cur_object)->c;
				//near_color = (t_color)2147483647U;
			}
		}
		shapes = shapes->next;
	}
	ray.dir = (vec3_scale(&ray.dir, nearest));
	intersection.p = *(t_point*)&ray.dir;
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
t_color	determine_color(t_point ip, t_color ic, t_list *lights, t_list *objects)
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
	double	x;
	double	y;

	double	u;
	double	v;
	// t_vec3	vp_point;
	const t_vec3 hrz = vec3_scale(&mini_rt->camera.right, mini_rt->camera.vp_width);
	const t_vec3 vrt = vec3_scale(&mini_rt->camera.up, mini_rt->camera.vp_height);
	const t_vec3 lower_left = vec3_substract((t_vec3 *)&mini_rt->camera.origin, &mini_rt->camera.dir);

	temp_ray = (t_ray) {mini_rt->camera.origin, (t_vec3) {0}};
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			u = (x + 0.5) / WIDTH * 2 - 1;
			v = (y + 0.5) / HEIGHT * 2 - 1;

			t_vec3 tmp = vec3_scale(&hrz, u);
			tmp = vec3_add(&lower_left, &tmp);
			t_vec3 tmp2 = vec3_scale(&vrt, v);
			temp_ray.dir = vec3_add(&tmp, &tmp2);
			temp_ray.dir = vec3_substract(&temp_ray.dir, (t_vec3 *)&mini_rt->camera.origin);
			temp_ray.dir = vec3_normalize(&temp_ray.dir);
			inter = check_intersect_obj(mini_rt, temp_ray);
			if (inter.t > 0)
			{
				my_mlx_pixel_put(&mini_rt->mlx.img, x, y,determine_color(inter.p, inter.c, mini_rt->lights, mini_rt->objects).trgb);
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
	if (ft_lstsize(mini_rt->lights) > 1)
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
	if (argc != 2 || !has_correct_extension(argv[1]))
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
	print_mini_rt(mini_rt);
	shoot_rays(&mini_rt);
	mlx_loop(mini_rt.mlx.mlx);
	destroy_mini_rt(&mini_rt);
	return (0);
}
