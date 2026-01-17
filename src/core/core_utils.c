/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:35:06 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/14 16:35:41 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_object	*get_ith_obj(t_vector *vector, size_t index)
{
	t_object	*array;

	if (index >= vector->nb_elements)
		return (NULL);
	array = (t_object *)(vector->array);
	return (&(array[index]));
}

t_light	*get_ith_light(t_vector *vector, size_t index)
{
	t_light	*array;

	if (index >= vector->nb_elements)
		return (NULL);
	array = (t_light *)(vector->array);
	return (&(array[index]));
}
