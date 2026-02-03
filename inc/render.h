/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:22:16 by abetemps          #+#    #+#             */
/*   Updated: 2026/01/17 16:32:06 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "miniRT.h"
# include "intersect.h"

// RENDER
void	render_scene(t_mini_rt *m_rt);

// RENDER UTILS

void	draw_intersection(t_mini_rt *m_rt, t_inter *inter, int i);
t_ray	create_ray(t_camera cam, int dth, int dtv);
t_color	get_color(t_inter inter, t_scene *scene);

#endif
