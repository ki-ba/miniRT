/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:27:35 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/08 15:13:15 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "parsing.h"
#include <unistd.h>

void	sfree(void **p)
{
	if (p)
		*p = NULL;
	free(*p);
}

void	destroy_shape(void *shape)
{
	free(((t_shape *)shape)->shape);
	free(((t_shape *)shape));
}

t_plane	*create_plane(char **specs)
{
	t_plane	*plane;

	if (arr_len(specs) < 4)
		return (NULL);
	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (NULL);
	if (read_point(&plane->p, specs[1]) || read_color(&plane->c, specs[3]))
	{
		free(plane);
		return (NULL);
	}
	if (read_normalized_vec(&plane->normal, specs[2]))
	{
		free(plane);
		return (NULL);
	}
	return (plane);
}

t_cylinder	*create_cylinder(char **specs)
{
	t_cylinder	*cyl;

	if (arr_len(specs) < 6)
		return (NULL);
	cyl = ft_calloc(1, sizeof(t_cylinder));
	if (!cyl)
		return (NULL);
	if (read_point(&cyl->center, specs[1]) || read_color(&cyl->c, specs[5]))
	{
		free(cyl);
		return (NULL);
	}
	if (read_normalized_vec(&cyl->normal, specs[2]))
	{
		free(cyl);
		return (NULL);
	}
	cyl->diameter = ft_strtod(specs[3]);
	cyl->height = ft_strtod(specs[4]);
	return (cyl);
}

t_sphere	*create_sphere(char **specs)
{
	t_sphere	*sp;

	if (arr_len(specs) < 4)
		return (NULL);
	sp = ft_calloc(1, sizeof(t_sphere));
	if (!sp)
		return (NULL);
	if (read_point(&sp->center, specs[1]) || read_color(&sp->c, specs[3]))
	{
		free(sp);
		return (NULL);
	}
	sp->diameter = ft_strtod(specs[2]);
	return (sp);
}

t_light	*create_light(char **specs)
{
	t_light	*light;

	if (arr_len(specs) < 4)
		return (NULL);
	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (NULL);
	if (read_color(&light->color, specs[3]))
	{
		free(light);
		return (NULL);
	}
	if (read_point(&light->origin, specs[1]))
	{
		free(light);
		return (NULL);
	}
	light->intensity = ft_strtod(specs[2]);
	return (light);
}
