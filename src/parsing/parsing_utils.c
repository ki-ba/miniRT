/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:38:40 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/10 11:34:43 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "libft.h"
#include "miniRT.h"

size_t	arr_len(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		++i;
	return (i);
}

/**
* @brief Convert a string to a double-precision floating-point number.
* @details This function handles one optional '+' or '-' at the start.
* @param n A pointer to a string pointer that will be updated to point to the
*         character following the last processed character in the input string.
* @param str The string to convert.
* @return The converted double value.
*/

double	ft_strtod(char *str, char **n)
{
	double	d;
	int		decimal;
	int		i;
	int		sign;

	if (!str || !n)
		return (0.0);
	sign = 1;
	if (str[0] == '-')
		sign = -1;
	decimal = ft_strlen_c(str, '.');
	i = (-1) + (str[0] == '+' || str[0] == '-');
	d = 0;
	while (str[++i])
	{
		if (i == decimal)
			continue ;
		else if (ft_isdigit(str[i]) == FALSE)
			break ;
		d += ((str[i] - '0')) / pow(10, i - decimal + (i < decimal));
	}
	*n = &str[i];
	return (sign * d);
}

/**
* @brief Check if the given filename has the correct extension.
* @param filename The name of the file to check.
* @return TRUE if the filename ends with the correct extension, FALSE otherwise.
*/
int	has_correct_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (FALSE);
	if (ft_strncmp(&filename[len - 3], EXTENSION, 4))
		return (FALSE);
	return (TRUE);
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
