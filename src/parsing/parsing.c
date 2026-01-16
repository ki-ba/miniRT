/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:19:13 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/12 15:20:59 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "miniRT.h"
#include "vec3.h"
#include "parsing.h"
#include "core.h"
#include "objects.h"
#include "debug.h"
#include "vectors.h"

void	print_obj(t_object obj);
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

int	set_camera(t_mini_rt *mini_rt, char **property)
{
	const double	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	t_vec3			world_up;
	t_vec3			tmp;
	char			*n;

	if (mini_rt->cam.is_defined)
		return (TOO_MUCH_ELEMENTS_ERR);
	mini_rt->cam.is_defined = TRUE;
	if (arr_len(property) < 4)
		return (GENERIC_ERR);
	if (read_point(&mini_rt->cam.ori, property[1]))
		return (GENERIC_ERR);
	if (read_normalized_vec(&mini_rt->cam.dir, property[2]) == INVALID_VALUE_ERR)
		return (GENERIC_ERR);
	mini_rt->cam.fov = deg_to_rad(ft_strtod(property[3], &n));
	world_up = (t_vec3) {0, 1, 0};
	if (fabs(vec3_dot(mini_rt->cam.dir, world_up)) > 0.999)
		world_up = (t_vec3){0,0,1};
	tmp = vec3_cross(world_up, mini_rt->cam.dir);
	mini_rt->cam.right = vec3_normalize(tmp);
	mini_rt->cam.up = vec3_cross(mini_rt->cam.dir, mini_rt->cam.right);
	mini_rt->cam.vp.vp_width = 2 * tan(mini_rt->cam.fov / 2) * VP_DISTANCE;
	mini_rt->cam.vp.vp_height = mini_rt->cam.vp.vp_width / aspect_ratio;
	return (*n != '\0');
}

int	set_amb(t_mini_rt *mini_rt, char **property)
{
	char	*n;

	if (mini_rt->amb.is_defined)
		return (TOO_MUCH_ELEMENTS_ERR);
	mini_rt->amb.is_defined = TRUE;
	if (arr_len(property) < 3)
		return (GENERIC_ERR);
	if (read_color(&mini_rt->amb.c, property[2]))
		return (GENERIC_ERR);
	mini_rt->amb.i = ft_strtod(property[1], &n);
	if (*n != '\0' || mini_rt->amb.i < 0.0
		|| mini_rt->amb.i > 1.0)
		return (GENERIC_ERR);
	return (0);
}

/**
	* @brief Set properties of miniRT structure based on provided property array.
	* @param mini_rt The main miniRT structure to populate.
	* @param property The array of strings representing property specifications.
	* @return 0 on success, or an error code on failure.
*/
int	set_property(t_mini_rt *mini_rt, char **property)
{
	int	status;

	status = 0;
	if (!ft_strncmp(property[0], CAMERA_ID, ft_strlen(CAMERA_ID) + 1))
		status = (set_camera(mini_rt, property));
	else if (!ft_strncmp(property[0], AMBIENT_ID, ft_strlen(AMBIENT_ID) + 1))
		status = (set_amb(mini_rt, property));
	if (status == TOO_MUCH_ELEMENTS_ERR)
		write(2, TOO_MUCH_ELEMENTS_MSG, ft_strlen(TOO_MUCH_ELEMENTS_MSG));
	return (status);
}

/**
 * @brief Format a line by trimming whitespace and splitting into tokens.
 * @param arr Pointer to store the resulting array of strings.
 * @param line The input line to format.
 * @return 0 on success, or an error code on failure.
 */
int	format_line(char ***arr, char *line)
{
	char	*trimmed_line;

	*arr = NULL;
	trimmed_line = ft_strtrim(line, WHITESPACES);
	if (!trimmed_line)
	{
		free(trimmed_line);
		return (MALLOC_ERR);
	}
	if (trimmed_line[0] == '#' || trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		return (COMMENT_OR_EMPTY_LINE);
	}
	*arr = ft_split(line, WHITESPACES);
	if (!arr)
	{
		free(trimmed_line);
		return (MALLOC_ERR);
	}
	free(trimmed_line);
	return (0);
}

/**
	* @brief Handle a single line from the input file.
	* @param mini_rt The main miniRT structure to populate.
	* @param line The line to process.
	* @return 0 on success, or an error code on failure.
*/
int	handle_line(t_mini_rt *mini_rt, char *line)
{
	int			(*p[5])(void *, char **);
	t_vector	**engine_lists[2];
	int			status;
	char		**object_arr;
	int			type;

	status = format_line(&object_arr, line);
	if (status > 0)
		return (!(status == COMMENT_OR_EMPTY_LINE));
	engine_lists[0] = &mini_rt->objects;
	engine_lists[1] = &mini_rt->lights;
	p[0] = &create_sphere;
	p[1] = &create_plane;
	p[2] = &create_cylinder;
	p[3] = &create_light;
	p[4] = NULL;
	type = define_item_type(object_arr[0]);
	if (is_property_id(object_arr[0]))
		status = (set_property(mini_rt, object_arr));
	else if (type >= 0)
		status = (add_item(engine_lists[type == LIGHT], p[type], object_arr));
	else
		status = INVALID_VALUE_ERR;
	ft_free_arr(object_arr);
	return (status);
}

int	parse_items_in_file(t_mini_rt *mini_rt, int fd)
{
	char	*line;
	int		status;

	status = 0;
	line = get_next_line(fd, &status);
	while (!status && line)
	{
		status = handle_line(mini_rt, line);
		if (status)
		{
			if (status > 0)
				printf("Error while parsing line: %s", line);
			free(line);
			return (status);
		}
		free(line);
		line = get_next_line(fd, &status);
	}
	printf("STATUS: %d\n", status);
	return (status);
}
