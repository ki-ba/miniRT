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

int	fill_double_array(double *slots[3], char **arr, size_t size)
{
	size_t	i;
	char	*n;

	i = 0;
	while (i < size)
	{
		*slots[i] = ft_strtod(arr[i], &n);
		if (*n != '\0')
			return (INVALID_VALUE_ERR);
		++i;
	}
	return (SUCCESS);
}

int	read_point(t_point *p, char *string)
{
	char	**arr;
	int		array_status;

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
	array_status = fill_double_array((double *[]){&p->x, &p->y, &p->z}, arr, 3);
	ft_free_arr(arr);
	return (array_status);
}

int	read_normalized_vec(t_vec3 *v, char *string)
{
	char	**arr;
	int		array_status;

	if (!string || !v)
		return (NULL_PARAM_ERR);
	arr = ft_split(string, ",");
	if (!arr)
		return (MALLOC_ERR);
	if (arr_len(arr) < 3)
	{
		ft_free_arr(arr);
		return (INVALID_VALUE_ERR);
	}
	array_status = fill_double_array((double *[]){&v->x, &v->y, &v->z}, arr, 3);
	ft_free_arr(arr);
	if (array_status != SUCCESS || is_normalized(*v) == FALSE)
		return (INVALID_VALUE_ERR);
	return (SUCCESS);
}
