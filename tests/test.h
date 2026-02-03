/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:08:42 by kbarru            #+#    #+#             */
/*   Updated: 2026/02/03 13:37:16 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

// PARSING

void	test_count_char_in_str(void);
void	test_ft_atoui_8(void);
void	test_check_extension(void);
void	test_ft_strtod(void);

// READ PROPERTIES

void	test_read_color(void);
void	test_read_point(void);
void	test_read_normalized_vec(void);

// OBJECTS

void	test_create_light(void);
void	test_create_plane(void);
void	test_create_cylinder(void);
void	test_create_sphere(void);

// VEC3

void	test_vec3_create(void);
void	test_vec3_add(void);
void	test_vec3_cross(void);
void	test_vec3_dot(void);
void	test_vec3_magnitude(void);
void	test_vec3_normalize(void);
void	test_vec3_scale(void);
void	test_vec3_sub(void);

// DEBUG

void	debug_test_function(void);
void	debug_utils_test_function(void);

// GRAPHICS

void	test_ft_init_mlx(void);
void	test_my_mlx_pixel_put(void);

// TEST HOOKS

void	test_handle_keypress_escape_exits_program(void);

// CORE

void	test_core(void);

// MATH

void	test_resolve_eq2(void);

// RENDERING

void	test_intersect_sphere(void);
void	test_determine_color(void);
void	test_shoot_rays(void);

// COLOR

void	test_scale_color(void);

// INTERSECT

void	test_check_intersect_sphere(void);
void	test_inter_cyl(void);

// UTILS

void	test_get_ith_obj(void);
void	test_get_ith_light(void);

// RENDER UTILS

void	test_draw_intersection(void);

// NORMAL

void	test_get_normal_sphere(void);

// HOOKS UTILS
void	test_is_set_bit(void);

#endif
