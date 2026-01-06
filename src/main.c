/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:04:24 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/06 10:41:07 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "parsing.h"
#include "miniRT.h"
#include "libft.h"
#include "core.h"
#include "math.h"

#include <math.h>
#include <fcntl.h>

void	set_point_color(t_mini_rt *mini_rt, t_point vp_point)
{
	t_vec3	ray;

	ray.x = vp_point.x - mini_rt->camera.origin.x;
	ray.y = vp_point.y - mini_rt->camera.origin.y;
	ray.z = vp_point.z - mini_rt->camera.origin.z;
}

t_vec3	normalize_vector(t_vec3 vector)
{
	double	magnitude;
	t_vec3	normalized;

	magnitude = sqrt(vector.x * vector.x + vector.y * vector.y
			+ vector.z * vector.z);
	if (magnitude == 0)
		return ((t_vec3){0, 0, 0});
	normalized.x = vector.x / magnitude;
	normalized.y = vector.y / magnitude;
	normalized.z = vector.z / magnitude;
	return (normalized);
}

t_ray	normalize_ray(t_ray ray)
{
	double	magnitude;
	t_ray	normalized;

	magnitude = sqrt(ray.x * ray.x + ray.y * ray.y
			+ ray.z * ray.z);
	if (magnitude == 0)
		return ((t_ray){ray.origin, 0, 0, 0});
	normalized.origin = ray.origin;
	normalized.x = ray.x / magnitude;
	normalized.y = ray.y / magnitude;
	normalized.z = ray.z / magnitude;
	return (normalized);
}

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

void	*get_inner_shape(t_list *shape)
{
	return (((t_shape *)shape->content)->shape);
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

/**
	* @brief for a given point, shoots towards each light 
	* @brief and calculates the color of the point.
*/
t_color	determine_color(t_point intersection, t_list *lights, t_list *objects)
{
	/* for every light, determine a vector from intersection to the light.
		If the vector finds any object, discard said light.
		It does not enlighten the intersection point.*/
	(void)intersection;
	(void)lights;
	(void)objects;
	return ((t_color)(uint32_t)0);
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
