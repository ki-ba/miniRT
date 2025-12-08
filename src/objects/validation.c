/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:15:27 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/08 13:16:23 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool	is_normalized(t_vec3 vector)
{
	if (vector.x < -1 || vector.x > 1)
		return (FALSE);
	if (vector.y < -1 || vector.y > 1)
		return (FALSE);
	if (vector.z < -1 || vector.z > 1)
		return (FALSE);
	return (TRUE);
}
