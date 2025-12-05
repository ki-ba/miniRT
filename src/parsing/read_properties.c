/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_properties.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:46:04 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/05 17:47:41 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "parsing.h"

double	read_array_field(size_t n, char *string)
{
	double	number;
	char	**array;

	array = ft_split(string, ",");
	number = ft_strtod(array[n]);
	ft_free_arr(array);
	return (number);
}

t_color	read_color(char *string)
{
	t_color	c;

	c.r = read_array_field(0, string);
	c.g = read_array_field(1, string);
	c.b = read_array_field(2, string);
	return (c);
}

t_point	read_point(char *string)
{
	t_point	p;

	p.x = read_array_field(0, string);
	p.y = read_array_field(1, string);
	p.z = read_array_field(2, string);
	return (p);
}

t_vec3	read_normalized_vec(char *string)
{
	t_vec3	v;

	v.x = read_array_field(0, string);
	v.y = read_array_field(1, string);
	v.z = read_array_field(2, string);
	return (v);
}
