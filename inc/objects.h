/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:44:54 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/17 15:41:21 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef OBJECTS_H
# define OBJECTS_H

# include "miniRT.h"

t_plane		*create_plane(char **specs);
t_cylinder	*create_cylinder(char **specs);
t_sphere	*create_sphere(char **specs);
t_light		*create_light(char **light_arr);
void		destroy_shape(void *shape);

#endif
