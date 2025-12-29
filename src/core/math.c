/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:25:58 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/18 13:33:46 by kbarru           ###   ########lyon.fr   */
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
