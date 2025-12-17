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
# include "libft.h"

void	print_item_lst(t_list *lst);
void	print_properties(t_mini_rt mini_rt);

// DEBUG_UTILS

void	print_point(char *name, t_point point);
void	print_color(char *name, t_color color);
void	print_vector(char *name, t_vec3 vector);

// DEBUG

void	print_cylinder(t_cylinder cy);
void	print_plane(t_plane pl);
void	print_sphere(t_sphere sp);
void	print_light(t_light l);
void	print_item_lst(t_list *lst);
#endif
