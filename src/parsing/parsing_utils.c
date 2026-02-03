/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:38:40 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/07 09:46:59 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "objects.h"
#include "parsing.h"

size_t	arr_len(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		++i;
	return (i);
}

/**
	* @brief Define the shape type based on the given identifier.
	* @param id The identifier string to check.
* @return The corresponding shape type constant, or -1 if unknown.
*/
int	define_item_type(char *id)
{
	if (ft_strncmp(id, SPHERE_ID, ft_strlen(id) + 1) == 0)
		return (SPHERE);
	else if (ft_strncmp(id, PLANE_ID, ft_strlen(id) + 1) == 0)
		return (PLANE);
	else if (ft_strncmp(id, CYLINDER_ID, ft_strlen(id) + 1) == 0)
		return (CYLINDER);
	else if (ft_strncmp(id, CONE_ID, ft_strlen(id) + 1) == 0)
		return (CONE);
	else if (ft_strncmp(id, LIGHT_ID, ft_strlen(id) + 1) == 0)
		return (LIGHT);
	return (-1);
}

/** 
	* @brief Check if the given id corresponds to a known property type.
	* @param id The identifier string to check.
* @return TRUE if the id matches a known property type, FALSE otherwise.
*/
int	is_property_id(char *id)
{
	if (ft_strncmp(id, CAMERA_ID, ft_strlen(CAMERA_ID) + 1) == 0)
		return (TRUE);
	else if (ft_strncmp(id, AMBIENT_ID, ft_strlen(AMBIENT_ID) + 1) == 0)
		return (TRUE + 1);
	return (FALSE);
}

/**
	* @brief Generic function to add an item to a vector.
	* @param lst The linked list to which the item will be added.
	* @param f The function used to create the item from the specifications.
	* @param item_arr The array of strings representing the item specifications.
*/
int	add_item(t_vector **objects, int (*f)(void *, char **), char **item_arr)
{
	t_object	obj;

	if (!objects)
		return (GENERIC_ERR);
	obj = (t_object){0};
	obj.type = define_item_type(item_arr[0]);
	if (f(&obj, item_arr))
		return (GENERIC_ERR);
	add_element(*objects, &obj);
	return (0);
}
