/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_magnitude.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:17:32 by abetemps          #+#    #+#             */
/*   Updated: 2026/01/07 09:34:36 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec3.h"

extern inline double	vec3_magnitude(t_vec3 v)
{
	return (sqrt(pow(v.x, 2.0) + pow(v.y, 2.0) + pow(v.z, 2.0)));
}
