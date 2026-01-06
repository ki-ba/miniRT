/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_substract.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:06:14 by abetemps          #+#    #+#             */
/*   Updated: 2025/12/19 17:16:12 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

extern inline t_vec3	vec3_substract(t_vec3 const *u, t_vec3 const *v)
{
	return ((t_vec3) {u->x - v->x, u->y - v->y, u->z - v->z});
}

