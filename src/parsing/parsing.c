/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:19:13 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/10 11:38:44 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "parsing.h"
#include "objects.h"

//TODO: document functions

/**
	* @brief Generic function to add an item to a linked list.
	* @param lst The linked list to which the item will be added.
	* @param f The function used to create the item from the specifications.
	* @param item_arr The array of strings representing the item specifications.
*/
int	add_item(t_list **lst, void *(*f)(char **), char **item_arr)
{
	t_list	*new_node;
	t_shape	*shape;
	void	*item;

	item = f(item_arr);
	shape = ft_calloc(1, sizeof(t_shape));
	new_node = ft_lstnew(shape);
	if (!item || !new_node || !shape)
	{
		ft_lstdelone(new_node, destroy_shape);
		free(item);
		return (GENERIC_ERR);
	}
	shape->shape = item;
	shape->type = define_item_type(item_arr[0]);
	ft_lstadd_back(lst, new_node);
	return (0);
}

// TODO: break down into separate functions for camera and ambient light

/**
	* @brief Set properties of miniRT structure based on provided property array.
	* @param mini_rt The main miniRT structure to populate.
	* @param property The array of strings representing property specifications.
	* @return 0 on success, or an error code on failure.
*/

int	set_property(t_miniRT *mini_rt, char **property)
{
	char	*n;

	if (!ft_strncmp(property[0], CAMERA_ID, ft_strlen(CAMERA_ID) + 1))
	{
		if (arr_len(property) < 4)
			return (GENERIC_ERR);
		if (read_point(&mini_rt->camera.origin, property[1]))
			return (GENERIC_ERR);
		if (read_normalized_vec(&mini_rt->camera.orientation, property[2]))
			return (GENERIC_ERR);
		mini_rt->camera.fov = ft_strtod(property[3], &n);
		return (*n != '\0');
	}
	else if (!ft_strncmp(property[0], AMBIENT_ID, ft_strlen(AMBIENT_ID) + 1))
	{
		if (arr_len(property) < 3)
			return (GENERIC_ERR);
		if (read_color(&mini_rt->ambient_light.color, property[2]))
			return (GENERIC_ERR);
		mini_rt->ambient_light.intensity = ft_strtod(property[1], &n);
		if (*n != '\0' || mini_rt->ambient_light.intensity < 0.0
			|| mini_rt->ambient_light.intensity > 1.0)
			return (GENERIC_ERR);
	}
	return (0);
}

/**
	* @brief Handle a single line from the input file.
	* @param mini_rt The main miniRT structure to populate.
	* @param line The line to process.
	* @return 0 on success, or an error code on failure.
*/
int	handle_line(t_miniRT *mini_rt, char *line)
{
	void	*(*p[5])(char **);
	t_list	**engine_lists[2];
	int		status;
	char	**object_arr;
	int		type;

	engine_lists[0] = &(mini_rt->objects);
	engine_lists[1] = &(mini_rt->lights);
	p[0] = (void *)&create_sphere;
	p[1] = (void *)&create_plane;
	p[2] = (void *)&create_cylinder;
	p[3] = (void *)&create_light;
	p[4] = NULL;
	if (!ft_strncmp("\n", line, 2))
		return (0);
	object_arr = ft_split(line, WHITESPACES);
	if (!object_arr)
		return (MALLOC_ERR);
	type = define_item_type(object_arr[0]);
	if (is_property_id(object_arr[0]))
		status = (set_property(mini_rt, object_arr));
	else
		status = (add_item(engine_lists[type == LIGHT], p[type], object_arr));
	ft_free_arr(object_arr);
	return (status);
}

int	parse_items_in_file(t_miniRT *mini_rt, int fd)
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
