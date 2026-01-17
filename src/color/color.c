/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:56:44 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/12 11:21:26 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include <math.h>

t_color	scale_color(t_color color, double scale)
{
	t_color	result;

	result.r = fmin(color.r * scale, 255);
	result.g = fmin(color.g * scale, 255);
	result.b = fmin(color.b * scale, 255);
	result.t = color.t;
	return (result);
}

t_color	mul_color(t_color c1, t_color c2)
{
	t_color	result;

	result.r = (c1.r * c2.r) / 255;
	result.g = (c1.g * c2.g) / 255;
	result.b = (c1.b * c2.b) / 255;
	result.t = c1.t;
	return (result);
}

t_color	add_color(t_color c1, t_color c2)
{
	t_color	result;

	result.r = fmin(c1.r + c2.r, 255);
	result.g = fmin(c1.g + c2.g, 255);
	result.b = fmin(c1.b + c2.b, 255);
	result.t = c1.t;
	return (result);
}
