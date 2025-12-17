/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:02:52 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/17 15:55:09 by kbarru           ###   ########lyon.fr   */
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
	return (0);
}
