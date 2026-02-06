/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:19:13 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/17 16:45:07 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "miniRT.h"
#include "vec3.h"
#include "parsing.h"
#include "core.h"
#include "objects.h"
#include "vectors.h"

int	set_camera(t_mini_rt *mini_rt, char **property)
{
	const double	aspect_ratio = (double)W / (double)H;
	char			*n;
	t_scene			*scene;
	t_vec3			*dir;

	scene = &mini_rt->scene;
	dir = &scene->cam.dir;
	if (scene->cam.is_defined)
		return (TOO_MUCH_ELEMENTS_ERR);
	scene->cam.is_defined = TRUE;
	if (arr_len(property) < 4 || read_point(&scene->cam.ori, property[1]))
		return (GENERIC_ERR);
	if (read_normalized_vec(&scene->cam.dir, property[2]) == INVALID_VAL_ERR)
		return (GENERIC_ERR);
	scene->cam.fov = deg_to_rad(ft_strtod(property[3], &n));
	scene->cam.wup = (t_vec3){0, 1, 0};
	if (fabs(vec3_dot(scene->cam.dir, scene->cam.wup)) > 0.999)
		scene->cam.wup = (t_vec3){0, 0, 1};
	scene->cam.right = vec3_normalize(vec3_cross(scene->cam.wup, *dir));
	scene->cam.up = vec3_cross(scene->cam.dir, scene->cam.right);
	scene->cam.vp.width = 2 * tan(scene->cam.fov / 2) * VP_DISTANCE;
	scene->cam.vp.height = scene->cam.vp.width / aspect_ratio;
	scene->cam.rot = (t_vec3){atan2(dir->z, dir->x), asin(dir->y), 0};
	return (*n != '\0');
}

int	set_amb(t_mini_rt *mini_rt, char **property)
{
	char	*n;
	t_scene	*scene;

	scene = &mini_rt->scene;
	if (scene->amb.is_defined)
		return (TOO_MUCH_ELEMENTS_ERR);
	scene->amb.is_defined = TRUE;
	if (arr_len(property) < 3)
		return (GENERIC_ERR);
	if (read_color(&scene->amb.c, property[2]))
		return (GENERIC_ERR);
	scene->amb.i = ft_strtod(property[1], &n);
	if (*n != '\0' || scene->amb.i < 0.0
		|| scene->amb.i > 1.0)
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
	* @brief Handle a single line from the input file.
	* @param mini_rt The main miniRT structure to populate.
	* @param line The line to process.
	* @return 0 on success, or an error code on failure.
*/
int	handle_line(t_mini_rt *mini_rt, char *line)
{
	int			(*p[E_ITEM_TYPE_QTY + 1])(void *, char **);
	int			status;
	int			type;
	char		**object_arr;
	t_vector	**engine_lists[2];

	status = format_line(&object_arr, line);
	if (status > 0)
		return (!(status == COMMENT_OR_EMPTY_LINE));
	engine_lists[0] = &mini_rt->scene.objects;
	engine_lists[1] = &mini_rt->scene.lights;
	p[0] = &create_sphere;
	p[1] = &create_plane;
	p[2] = &create_cylinder;
	p[3] = &create_light;
	p[4] = NULL;
	type = define_item_type(object_arr[0]);
	status = INVALID_VAL_ERR;
	if (is_property_id(object_arr[0]))
		status = (set_property(mini_rt, object_arr));
	else if (type >= 0)
		status = (add_item(engine_lists[type == LIGHT], p[type], object_arr));
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
	return (status);
}
