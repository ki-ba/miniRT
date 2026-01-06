/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:25:58 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/06 10:40:40 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include <math.h>



/**
*	@brief Resolve a quadratic equation of the form ax^2 + bx + c = 0
*	@param a Coefficient of x^2
*	@param b Coefficient of x
*	@param c Constant term
*	@return TRUE if equation has a solution in R,
*	@return FALSE otherwise.
*/
t_bool	resolve_eq2(double a, double b, double c, double *root)
{
	double discriminant;

	// printf("Resolving equation %fx^2 + %fx + %f = 0\n", a, b, c);
	*root = 0;
	if (!root || a == 0)
		return (FALSE);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (FALSE);
	else
		*root = (-b - sqrt(discriminant)) / (2 * a);
	if (*root < 0)
		*root = (-b + sqrt(discriminant)) / (2 * a);
	return (TRUE);
}

/**
	* @brief computes a point along a ray at distance t from the ray origin.
*/
t_point	vec_to_point(t_ray ray, double t)
{
	t_point	point;

	point.x = ray.origin.x + ray.dir.x * t;
	point.y = ray.origin.y + ray.dir.y * t;
	point.z = ray.origin.z + ray.dir.z * t;
	return (point);
}

/**
*	@brief Converts an angle in degrees to radiants
*	@param deg Degrees' angle to convert
*	@return Converted angle
*/
extern inline double	deg_to_rad(double deg)
{
	return (deg * (M_PI / 180));
}
