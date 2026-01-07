/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:44:54 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/07 09:41:00 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef OBJECTS_H
# define OBJECTS_H

# include "miniRT.h"

typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_sphere		t_sphere;
typedef struct s_shape		t_shape;

struct s_plane
{
	t_point	p;
	t_color	c;
	t_vec3	normal;
};

struct s_cylinder
{
	t_point	center;
	t_color	c;
	t_vec3	normal;
	double	diameter;
	double	height;
};

struct s_sphere
{
	t_point	center;
	t_color	c;
	double	diameter;
};

struct s_shape
{
	enum e_item_type	type;
	void				*shape;
};

t_plane		*create_plane(char **specs);
t_cylinder	*create_cylinder(char **specs);
t_sphere	*create_sphere(char **specs);
t_light		*create_light(char **light_arr);
void		destroy_shape(void *shape);

#endif
