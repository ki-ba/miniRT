/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:22:16 by abetemps          #+#    #+#             */
/*   Updated: 2026/01/12 09:53:36 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "miniRT.h"

// double	check_intersect_sphere(t_object *sp, t_ray ray);
// t_inter	check_intersect_obj(t_mini_rt *mini_rt, t_ray ray);
// t_color	get_color(t_vec3 ip, t_color ic, t_vector *lights, t_object *objects;
void	shoot_rays(t_mini_rt *mini_rt);

#endif
