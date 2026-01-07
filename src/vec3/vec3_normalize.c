/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:34:36 by abetemps          #+#    #+#             */
/*   Updated: 2026/01/07 09:34:03 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

double	vec3_magnitude(t_vec3 v);

extern inline t_vec3	vec3_normalize(t_vec3 v)
{
	const double	v_mag = vec3_magnitude(v);

	if (!v_mag)
		return ((t_vec3){0.0, 0.0, 0.0});
	return ((t_vec3) {v.x / v_mag, v.y / v_mag, v.z / v_mag});
}
