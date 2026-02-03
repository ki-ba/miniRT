/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:19:48 by kbarru            #+#    #+#             */
/*   Updated: 2026/02/03 14:44:00 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "hooks.h"
# include "vec3.h"
# include "vectors.h"
# include "graphics.h"
# include "color.h"

# define VP_DISTANCE 1
# define SHININESS 50

/* ENUMS */
enum e_error_code
{
	SUCCESS = 0,
	GENERIC_ERR,
	NULL_PARAM_ERR,
	INVALID_VAL_ERR,
	MALLOC_ERR,
	TOO_MUCH_ELEMENTS_ERR,
	VECTOR_NOT_NORMALIZED_ERR,
	COMMENT_OR_EMPTY_LINE,
	E_ERROR_CODE_QTY
};

/* UTILS */
typedef struct s_ray		t_ray;
typedef struct s_light		t_light;
typedef struct s_ambient	t_ambient;
typedef struct s_camera		t_camera;
typedef struct s_mini_rt	t_mini_rt;
typedef struct s_viewport	t_viewport;
typedef struct s_scene		t_scene;

struct s_ray
{
	t_vec3	ori;
	t_vec3	dir;
};

/* SCENE */
struct s_ambient
{
	t_bool	is_defined;
	t_color	c;
	double	i;
};

struct s_light
{
	t_vec3	ori;
	t_color	c;
	double	i;
};

struct s_viewport
{
	t_vec3	ori;
	t_vec3	hrz;
	t_vec3	vrt;
	double	delta_h;
	double	delta_v;
	double	height;
	double	width;
};

struct s_camera
{
	t_bool				is_defined;
	t_vec3				ori;
	t_vec3				dir;
	t_vec3				wup;
	t_vec3				up;
	t_vec3				right;
	t_viewport			vp;
	double				fov;
	t_vec3				rot;
};

struct s_scene
{
	t_vector	*objects;
	t_vector	*lights;
	t_camera	cam;
	t_ambient	amb;
};

struct s_mini_rt
{
	int			scale;
	t_hooks		mode;
	t_scene		scene;
	t_mlx		mlx;
};

#endif
