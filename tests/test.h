/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:08:42 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/19 17:48:08 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

// PARSING

void	test_count_char_in_str(void);
void	test_ft_atoui_8(void);
void	test_has_correct_extension(void);
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

void	test_vec3_add(void);
void	test_vec3_cross(void);
void	test_vec3_dot(void);
void	test_vec3_magnitude(void);
void	test_vec3_normalize(void);
void	test_vec3_scale(void);
void	test_vec3_substract(void);

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
#endif
