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
typedef struct s_object		t_object;
typedef enum e_item_type	t_item_type;

struct s_plane
{
	t_vec3	p;
};

enum e_item_type
{
	SPHERE = 0,
	PLANE,
	CYLINDER,
	LIGHT,
	E_ITEM_TYPE_QTY
};

struct s_object
{
	t_item_type	type;
	t_vec3		center;
	t_vec3		n;
	t_vec3		p;
	t_color		c;
	double		diam;
	double		h;

};

int	create_plane(void *plane, char **specs);
int	create_cylinder(void *cyl, char **specs);
int	create_sphere(void *sp, char **specs);
int	create_light(void *light, char **light_arr);

#endif
