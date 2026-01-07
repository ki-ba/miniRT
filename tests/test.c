/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:02:52 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/07 15:29:25 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "test.h"

void	setUp(void)
{
}

void	tearDown(void)
{
}

int	main(void)
{
	// PARSING TESTS
	RUN_TEST(test_count_char_in_str);
	RUN_TEST(test_ft_atoui_8);
	RUN_TEST(test_ft_strtod);
	RUN_TEST(test_has_correct_extension);
	// READ PROPERTIES TESTS
	RUN_TEST(test_read_color);
	RUN_TEST(test_read_point);
	RUN_TEST(test_read_normalized_vec);
	// OBJECTS TESTS
	RUN_TEST(test_create_light);
	RUN_TEST(test_create_plane);
	RUN_TEST(test_create_cylinder);
	RUN_TEST(test_create_sphere);
	// VEC3 TESTS
	RUN_TEST(test_vec3_create);
	RUN_TEST(test_vec3_add);
	RUN_TEST(test_vec3_substract);
	RUN_TEST(test_vec3_scale);
	RUN_TEST(test_vec3_magnitude);
	RUN_TEST(test_vec3_dot);
	RUN_TEST(test_vec3_normalize);
	RUN_TEST(test_vec3_cross);
	// DEBUG TESTS
	RUN_TEST(debug_test_function);
	RUN_TEST(debug_utils_test_function);
	// GRAPHICS TESTS
	RUN_TEST(test_ft_init_mlx);
	RUN_TEST(test_my_mlx_pixel_put);
	// HOOKS TESTS
	RUN_TEST(test_handle_keypress_escape_exits_program);
	// CORE TESTS
	RUN_TEST(test_core);
	// MATH TESTS
	RUN_TEST(test_resolve_eq2);

	// RENDER
	
	RUN_TEST(test_intersect_sphere);
	RUN_TEST(test_determine_color);
	RUN_TEST(test_shoot_rays);
	return (0);
}
