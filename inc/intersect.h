/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:25:58 by kbarru            #+#    #+#             */
/*   Updated: 2026/02/03 13:30:22 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "objects.h"
# include "miniRT.h"

# define N_HITTABLE_TYPES 3

typedef struct s_inter		t_inter;

struct s_inter
{
	t_vec3			p;
	t_vec3			n;
	t_ray			ray;
	struct s_object	*obj;
	double			t;
};

int		is_in_shadow(t_vector *objects, t_light *light, t_inter inter);
t_inter	check_intersect_obj(t_vector *objects, t_ray ray);
t_vec3	get_normal_at_intersection(t_inter inter);
double	intersect_cylinder(t_object *cy, t_ray ray);

#endif
