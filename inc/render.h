/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:22:16 by abetemps          #+#    #+#             */
/*   Updated: 2026/01/14 16:28:22 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "miniRT.h"
# include "intersect.h"

# define	LQ_STEP 10

void	shoot_rays(t_mini_rt *mini_rt);

// RENDER UTILS
void	draw_intersection(t_mini_rt *m_rt, t_inter *inter, int *i);
t_ray	create_ray(t_camera cam, int index);
t_color	get_color(t_vector *objects, t_ambient amb, t_inter inter, t_light *l);

#endif
