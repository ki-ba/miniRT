/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:26:18 by kbarru            #+#    #+#             */
/*   Updated: 2026/02/03 13:30:27 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"
#include <math.h>
#include "core.h"

#define N_CAP 0 // cap normal
#define C_CAP 1 // cap center
#define P_CAP 2 // point of intersection

double	intersect_cone(t_object *co, t_ray ray)
{
	double		root;

	(void)co;
	(void)ray;
	root = 1;
	return (root);
}

