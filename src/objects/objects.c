/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:27:35 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/07 09:42:02 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parsing.h"
#include "objects.h"
#include <unistd.h>

int	create_plane(void *plane, char **specs)
{
	t_object	*c_plane;

	c_plane = (t_object *)plane;
	if (arr_len(specs) < 4)
		return (INVALID_VALUE_ERR);
	if (read_point(&c_plane->p, specs[1]) || read_color(&c_plane->c, specs[3]))
		return (INVALID_VALUE_ERR);
	if (read_normalized_vec(&c_plane->n, specs[2]))
		return (VECTOR_NOT_NORMALIZED_ERR);
	return (0);
}

int	create_cylinder(void *cyl, char **specs)
{
	char		*n;
	char		*n2;
	t_object	*c_cyl;

	c_cyl = (t_object *)cyl;
	if (arr_len(specs) < 6)
		return (INVALID_VALUE_ERR);
	if (!cyl || read_normalized_vec(&c_cyl->n, specs[2]))
		return (INVALID_VALUE_ERR);
	if (read_point(&c_cyl->center, specs[1]) || read_color(&c_cyl->c, specs[5]))
		return (INVALID_VALUE_ERR);
	c_cyl->diam = ft_strtod(specs[3], &n);
	c_cyl->h= ft_strtod(specs[4], &n2);
	if (*n != '\0' || *n2 != '\0')
		return (INVALID_VALUE_ERR);
	return (0);
}

int	create_sphere(void *sp, char **specs)
{
	char		*n;
	t_object	*c_sp;

	c_sp = (t_object *)sp;
	if (arr_len(specs) < 4)
		return (INVALID_VALUE_ERR);
	if (read_point(&c_sp->center, specs[1]) || read_color(&c_sp->c, specs[3]))
		return (INVALID_VALUE_ERR);
	c_sp->diam = ft_strtod(specs[2], &n);
	if (*n != '\0')
		return (INVALID_VALUE_ERR);
	return (0);
}

int	create_light(void *light, char **specs)
{
	char		*n;
	t_light		*c_light;

	c_light = (t_light *)light;
	if (arr_len(specs) < 4)
		return (INVALID_VALUE_ERR);
	if (read_color(&c_light->c, specs[3]))
		return (INVALID_VALUE_ERR);
	if (read_point(&c_light->ori, specs[1]))
		return (INVALID_VALUE_ERR);
	c_light->i = ft_strtod(specs[2], &n);
	if (*n != '\0' || c_light->i < 0.0 || c_light->i > 1.0)
		return (INVALID_VALUE_ERR);
	return (0);
}
