/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:27:35 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/05 18:25:23 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "parsing.h"
#include <unistd.h>

void	destroy_shape(void *shape)
{
	free(((t_shape *)shape)->shape);
	free(((t_shape *)shape));
}

t_plane	*create_plane(char **specs)
{
	t_plane	*plane;

	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->p = read_point(specs[1]);
	plane->c = read_color(specs[3]);
	plane->normal = read_normalized_vec(specs[2]);
	if (is_normalized(plane->normal) == FALSE)
	{
		free(plane);
		return (NULL);
	}
	return (plane);
}

t_cylinder	*create_cylinder(char **specs)
{
	t_cylinder	*cylinder;

	cylinder = ft_calloc(1, sizeof(t_cylinder));
	cylinder->center = read_point(specs[1]);
	cylinder->normal = read_normalized_vec(specs[2]);
	if (is_normalized(cylinder->normal) == FALSE)
	{
		free(cylinder);
		return (NULL);
	}
	cylinder->diameter = ft_strtod(specs[3]);
	cylinder->height = ft_strtod(specs[4]);
	cylinder->c = read_color(specs[5]);
	return (cylinder);
}

t_sphere	*create_sphere(char **specs)
{
	t_sphere	*sphere;

	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = read_point(specs[1]);
	sphere->diameter = ft_strtod(specs[2]);
	sphere->c = read_color(specs[3]);
	return (sphere);
}

t_light	*create_light(char **light_arr)
{
	t_light	*light;

	(void)light_arr;
	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (NULL);
	light->color = read_color(light_arr[3]);
	light->origin.x = read_array_field(0, light_arr[1]);
	light->origin.y = read_array_field(1, light_arr[1]);
	light->origin.z = read_array_field(2, light_arr[1]);
	light->intensity = ft_strtod(light_arr[2]);
	return (light);
}
