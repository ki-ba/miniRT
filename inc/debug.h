/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:50:13 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/10 11:28:25 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "miniRT.h"
# include "objects.h"
# include "vectors.h"

void	print_properties(t_mini_rt mini_rt);

// DEBUG_UTILS

void	print_vec3(char *name, t_vec3 point);
void	print_color(char *name, t_color color);
void	print_vector(char *name, t_vec3 vector);

// DEBUG

void	print_item_lst(t_vector *objects);
void	print_lights(t_vector *lights);
void	print_cylinder(t_object obj);
#endif
