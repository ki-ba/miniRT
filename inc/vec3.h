/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:43:22 by abetemps            #+#    #+#             */
/*   Updated: 2026/01/06 17:48:30 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		VEC3_H
# define	VEC3_H

# include "miniRT.h"

t_vec3	vec3_create(t_point const *o, t_point const *d);
t_vec3	vec3_add(t_vec3 const *u, t_vec3 const *v);
t_vec3	vec3_substract(t_vec3 const *u, t_vec3 const *v);
t_vec3	vec3_scale(t_vec3 const *v, double s);
t_vec3	vec3_cross(t_vec3 const *u, t_vec3 const *v);
t_vec3	vec3_normalize(t_vec3 const *v);
double	vec3_magnitude(t_vec3 const *v);
double	vec3_dot(t_vec3 const *u, t_vec3 const *v);

#endif
