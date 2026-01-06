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
*	@return A pointer to a t_roots structure containing the roots and delta,
*	@return or NULL if memory allocation fails
*/
t_roots	*resolve_eq2(double a, double b, double c)
{
	t_roots	*roots;
	static int	call_count = 0;

	(void)call_count;
	if (a == 0)
		return (NULL);
	// printf("%d : Resolving equation: %fx^2 + %fx + %f = 0\n",call_count++, a, b, c);
	roots = ft_calloc(1, sizeof(t_roots));
	if (!roots)
		return (NULL);
	roots->delta = b * b - 4 * a * c;
	if (roots->delta < 0)
		return (roots);
	if (roots->delta == 0)
	{
		roots->root1 = -b / (2 * a);
		return (roots);
	}
	else
	{
		roots->root1 = (-b - sqrt(roots->delta)) / (2 * a);
		roots->root2 = (-b + sqrt(roots->delta)) / (2 * a);
	}
	return (roots);
}

/**
	* @brief returns a valid solution for given 2nd order equation.
	* @returns the smallest positive value if delta > 0,
	* @returns the only solution if delta == 0,
	* @returns -1 if given equation has no real solution.
*/
double	get_solution(double a, double b, double c)
{
	t_roots	*roots;
	double	solution;

	roots = resolve_eq2(a, b, c);
	if (!roots)
		return (-1);
	solution = -1;
	if (roots->delta < 0)
		solution = -1;
	else if (roots->delta == 0)
	{
		if (roots->root1 > 0)
			solution = roots->root1;
	}
	else
	{
		if (roots->root1 > 0 && roots->root2 > 0)
			solution = fmin(roots->root1, roots->root2);
		else if (roots->root1 > 0)
			solution = roots->root1;
		else if (roots->root2 > 0)
			solution = roots->root2;
	}
	free(roots);
	return (solution);
}

/**
	* @brief computes a point along a ray at distance t from the ray origin.
*/
t_point	vec_to_point(t_ray ray, double t)
{
	t_point	point;

	point.x = ray.origin.x + ray.x * t;
	point.y = ray.origin.y + ray.y * t;
	point.z = ray.origin.z + ray.z * t;
	return (point);
}
