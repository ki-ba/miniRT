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

# include	"miniRT.h"
# include	"vec3.h"

int			render_scene(t_mini_rt *mini_rt);
int			trace_rays(t_mini_rt *mini_rt);
t_vector	*find_intersections(t_point const *pos, t_vec3 const *dir, t_mini_rt const *mini_rt, const t_item_type mode);

#endif
