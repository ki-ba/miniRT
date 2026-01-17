/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_properties.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:46:04 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/17 16:43:30 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "vec3.h"
#include "parsing.h"
#include <math.h>

t_bool	is_normalized(t_vec3 vector)
{
	if (vector.x < -1 || vector.x > 1)
		return (FALSE);
	if (vector.y < -1 || vector.y > 1)
		return (FALSE);
	if (vector.z < -1 || vector.z > 1)
		return (FALSE);
	return (sqrt(vector.x * vector.x + vector.y * vector.y
			+ vector.z * vector.z) <= 1.0);
}

int	read_color(t_color *c, char *string)
{
	char	**arr;
	char	*n;
	int		status;

	status = SUCCESS;
	if (!c || !string)
		return (NULL_PARAM_ERR);
	arr = ft_split(string, ",");
	if (!arr)
		return (MALLOC_ERR);
	if (count_char_in_str(string, ',') != 2 || arr_len(arr) < 3)
	{
		ft_free_arr(arr);
		return (INVALID_VAL_ERR);
	}
	c->r = ft_atoui_8(arr[0], &n);
	if (*n != 0)
		status = (INVALID_VAL_ERR);
	c->g = ft_atoui_8(arr[1], &n);
	if (*n != 0)
		status = (INVALID_VAL_ERR);
	c->b = ft_atoui_8(arr[2], &n);
	ft_free_arr(arr);
	return ((*n != 0) & status);
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
			return (INVALID_VAL_ERR);
		++i;
	}
	return (SUCCESS);
}

int	read_point(t_vec3 *p, char *string)
{
	char	**arr;
	int		array_status;

	if (!p || !string)
		return (NULL_PARAM_ERR);
	if (count_char_in_str(string, ',') != 2)
		return (INVALID_VAL_ERR);
	arr = ft_split(string, ",");
	if (!arr)
		return (MALLOC_ERR);
	if (arr_len(arr) < 3)
	{
		ft_free_arr(arr);
		return (INVALID_VAL_ERR);
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
	if (count_char_in_str(string, ',') != 2 || arr_len(arr) < 3)
	{
		ft_free_arr(arr);
		return (INVALID_VAL_ERR);
	}
	array_status = fill_double_array((double *[]){&v->x, &v->y, &v->z}, arr, 3);
	ft_free_arr(arr);
	if (array_status != SUCCESS)
		return (INVALID_VAL_ERR);
	else if (v->x == 0 && v->y == 0 && v->z == 0)
	{
		write(2, VECTOR_NOT_NORMALIZED, ft_strlen(VECTOR_NOT_NORMALIZED));
		return (INVALID_VAL_ERR);
	}
	else if (is_normalized(*v) == FALSE)
		*v = vec3_normalize(*v);
	return (SUCCESS);
}
