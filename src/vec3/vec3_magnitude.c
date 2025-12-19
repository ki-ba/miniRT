/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_magnitude.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:17:32 by abetemps          #+#    #+#             */
/*   Updated: 2025/12/19 17:25:22 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "miniRT.h"

double	vec3_magnitude(t_vec3 const *v)
{
	return (sqrt(pow(v->x, 2.0) + pow(v->y, 2.0) + pow(v->z, 2.0)));
}

