/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:34:36 by abetemps          #+#    #+#             */
/*   Updated: 2025/12/19 17:39:12 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	vec3_magnitude(t_vec3 const *v);

t_vec3	vec3_normalize(t_vec3 const *v)
{
	const double v_mag = vec3_magnitude(v);

	if (!v_mag)
		return ((t_vec3) {0.0, 0.0, 0.0});
	return ((t_vec3) {v->x / v_mag, v->y / v_mag, v->z / v_mag});
}

