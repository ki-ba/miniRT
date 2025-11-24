/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:19:48 by kbarru            #+#    #+#             */
/*   Updated: 2025/11/20 15:20:04 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdint.h>

# define EXTENSION ".rt"
# define PLANE "pl"
# define CYLINDER "cy"
# define SPHERE "sp"
# define AMBIENT "A"
# define LIGHT "L"
# define CAMERA "C"

/* UTILS */

typedef union color
{
	int8_t	r;
	int8_t	g;
	int8_t	b;
}	t_color;

typedef struct s_vec3
{
	int	x;
	int	y;
	int	z;
}	t_vec3;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
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


#endif
