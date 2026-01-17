/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:43:22 by abetemps          #+#    #+#             */
/*   Updated: 2026/01/07 09:35:46 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

typedef struct s_vec3		t_vec3;

t_vec3	vec3_create(t_vec3 o, t_vec3 d);
t_vec3	vec3_add(t_vec3 u, t_vec3 v);
t_vec3	vec3_substract(t_vec3 u, t_vec3 v);
t_vec3	vec3_scale(t_vec3 v, double s);
t_vec3	vec3_cross(t_vec3 u, t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);
double	vec3_magnitude(t_vec3 v);
double	vec3_dot(t_vec3 u, t_vec3 v);

#endif
