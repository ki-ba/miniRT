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

typedef struct s_inter		t_inter;

struct s_inter
{
	t_vec3			p;
	t_vec3			n;
	struct s_object	*obj;
	double			t;
};

t_inter	check_intersect_obj(t_vector *objects, t_ray ray);
int		is_in_shadow(t_vector *objects, t_light *light, t_vec3 point);
t_vec3	get_normal_sphere(t_inter inter);
t_vec3	get_normal_plane(t_inter inter);
t_vec3	get_normal_cylinder(t_inter inter);
t_vec3	get_normal_cone(t_inter inter);
t_vec3	get_normal_at_intersection(t_inter inter);

// Intersect cone 

double	inter_cyl_caps(t_object *cy, t_ray ray, const double r, const bool tb);
double	inter_cyl_body(t_object *cy, t_ray ray, double dir_norm, double r);
double	intersect_cylinder(t_object *cy, t_ray ray);
double	intersect_cone(t_object *co, t_ray ray);

#endif
