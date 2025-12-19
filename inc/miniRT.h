/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:19:48 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/17 15:50:27 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"
# include "graphics.h"
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

# define WIDTH 1920
# define HEIGHT 1080


typedef enum	e_item_type	t_item_type;
typedef union	u_color		t_color;
typedef struct	s_vec3		t_vec3;
typedef struct	s_point		t_point;
typedef struct	s_light		t_light;
typedef struct	s_plane		t_plane;
typedef struct	s_cylinder	t_cylinder;
typedef struct	s_sphere	t_sphere;
typedef struct	s_shape		t_shape;
typedef struct	s_ambient	t_ambient;
typedef struct	s_camera	t_camera;
typedef struct	s_mlx		t_mlx;
typedef struct	s_mini_rt	t_mini_rt;

/* ENUMS */
enum e_error_code
{
	SUCCESS = 0,
	GENERIC_ERR,
	NULL_PARAM_ERR,
	INVALID_VALUE_ERR,
	MALLOC_ERR,
	E_ERROR_CODE_QTY
};

enum e_item_type
{
	SPHERE = 0,
	PLANE,
	CYLINDER,
	LIGHT,
	E_ITEM_TYPE_QTY
};

/* UTILS */
union u_color
{
	uint32_t trgb;
	struct
	{
		uint8_t	t;
		uint8_t	r;
		uint8_t	g;
		uint8_t	b;
	};
};

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};


struct s_point
{
	double	x;
	double	y;
	double	z;
};

struct s_light
{
	t_point	origin;
	t_color	color;
	double	intensity;
};

/* OBJECTS */
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

/* SCENE */
struct s_ambient
{
	t_bool	is_defined;
	double	intensity;
	t_color	color;
};

struct s_camera
{
	t_bool	is_defined;
	t_point	origin;
	t_vec3	orientation;
	int		fov;
};

// struct s_mlx
// {
// 	void		*mlx;
// 	void		*win;
// 	t_data		img;
// };

struct s_mini_rt
{
	t_list		*objects;
	t_list		*lights;
	t_camera	camera;
	t_ambient	ambient_light;
	// t_mlx		mlx;		//maybe to extract
	void		*mlx;
	void		*win;
	t_data		img;
};

#endif
