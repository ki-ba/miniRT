/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:22:16 by abetemps          #+#    #+#             */
/*   Updated: 2025/12/23 10:50:01 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		RENDERING_H
# define	RENDERING_H

#include "miniRT.h"
#include "libft.h"
#include "objects.h"

// double	check_intersect_sphere(t_object *sp, t_ray ray);
// t_inter	check_intersect_obj(t_mini_rt *mini_rt, t_ray ray);
// t_color	determine_color(t_vec3 ip, t_color ic, t_vector *lights, t_vector *objects);
void	shoot_rays(t_mini_rt *mini_rt);

#endif
