/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_properties.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:46:04 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/08 15:16:31 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "parsing.h"

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

int	read_color(t_color *c, char *string)
{
	char	**arr;

	if (!c)
		return (NULL_PARAM_ERR);
	arr = ft_split(string, ",");
	if (!arr)
		return (MALLOC_ERR);
	if (arr_len(arr) < 3)
	{
		ft_free_arr(arr);
		return (INVALID_VALUE_ERR);
	}
	c->r = ft_atoi(arr[0]);
	c->g = ft_atoi(arr[1]);
	c->b = ft_atoi(arr[2]);
	ft_free_arr(arr);
	return (0);
}

int	read_point(t_point *p, char *string)
{
	char	**arr;

	if (!p)
		return (NULL_PARAM_ERR);
	arr = ft_split(string, ",");
	if (!arr)
		return (MALLOC_ERR);
	if (arr_len(arr) < 3)
	{
		ft_free_arr(arr);
		return (INVALID_VALUE_ERR);
	}
	p->x = ft_strtod(arr[0]);
	p->y = ft_strtod(arr[1]);
	p->z = ft_strtod(arr[2]);
	ft_free_arr(arr);
	return (0);
}

int	read_normalized_vec(t_vec3 *v, char *string)
{
	char	**arr;

	if (!v)
		return (NULL_PARAM_ERR);
	arr = ft_split(string, ",");
	if (!arr)
		return (MALLOC_ERR);
	if (arr_len(arr) < 3)
	{
		ft_free_arr(arr);
		return (INVALID_VALUE_ERR);
	}
	v->x = ft_strtod(arr[0]);
	v->y = ft_strtod(arr[1]);
	v->z = ft_strtod(arr[2]);
	ft_free_arr(arr);
	return ((is_normalized(*v) == FALSE) * (-1));
}
