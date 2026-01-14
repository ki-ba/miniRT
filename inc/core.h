/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:52:34 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/14 16:37:07 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "miniRT.h"
# include "objects.h"

typedef struct s_roots
{
	double	root1;
	double	root2;
	double	delta;
}			t_roots;

void		destroy_mini_rt(t_mini_rt *mini_rt);
void		init_mini_rt(t_mini_rt *mini_rt);
void		print_mini_rt(t_mini_rt *mini_rt);
void		clean_exit(t_mini_rt *mini_rt, int exit_code);
void		init_vp(t_camera *cam);

// MATH

t_bool		resolve_eq2(double a, double b, double c, double *root);
double		deg_to_rad(double deg);
t_vec3		vec_to_point(t_ray ray, double t);
double		deg_to_rad(double deg);

// UTILS

t_object	*get_ith_obj(t_vector *vector, size_t index);
t_light		*get_ith_light(t_vector *vector, size_t index);
#endif
