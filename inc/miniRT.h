/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:19:48 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/10 11:36:08 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include <stdint.h>

# define EXTENSION ".rt"
# define PLANE_ID "pl"
# define CYLINDER_ID "cy"
# define SPHERE_ID "sp"
# define AMBIENT_ID "A"
# define LIGHT_ID "L"
# define CAMERA_ID "C"

# define USAGE_ERR_MSG "usage : ./miniRT filename.rt\n"
# define FILE_ERR_MSG "Error while reading file\n"
# define MISSING_PROPERTY_MSG "Error: Missing required property (A or C)\n"

typedef enum e_error_code
{
	SUCCESS = 0,
	NULL_PARAM_ERR = 1,
	INVALID_VALUE_ERR,
	MALLOC_ERR,
	GENERIC_ERR
}	t_error_code;

/* UTILS */

typedef enum e_item_type
{
	SPHERE = 0,
	PLANE,
	CYLINDER,
	LIGHT
}	t_item_type;

typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_color;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct s_light
{
	t_point	origin;
	t_color	color;
	double	intensity;
}	t_light;

/* OBJECTS */

typedef struct s_plane
{
	t_point	p;
	t_color	c;
	t_vec3	normal;
}	t_plane;

typedef struct s_cylinder
{
	t_point	center;
	t_color	c;
	t_vec3	normal;
	double	diameter;
	double	height;
}	t_cylinder;

typedef struct s_sphere
{
	t_point	center;
	t_color	c;
	double	diameter;
}	t_sphere;

typedef struct s_shape
{
	enum e_item_type	type;
	void				*shape;
}	t_shape;

typedef struct s_ambient
{
	t_bool	is_defined;
	double	intensity;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_bool	is_defined;
	t_point	origin;
	t_vec3	orientation;
	int		fov;
}	t_camera;

typedef struct s_miniRT
{
	t_list		*objects;
	t_list		*lights;
	t_camera	camera;
	t_ambient	ambient_light;
}	t_miniRT;

// DESTROY

void			destroy_shape(void *shape);
void			destroy_mini_rt(t_miniRT *miniRT);

#endif
