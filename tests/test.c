/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:02:52 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/08 14:37:20 by kbarru           ###   ########lyon.fr   */
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
	RUN_TEST(test_has_correct_extension);
	RUN_TEST(test_ft_strtod);

	// READ PROPERTIES TESTS
	RUN_TEST(test_read_color);
	RUN_TEST(test_read_point);
	RUN_TEST(test_read_normalized_vec);


	// OBJECTS TESTS
	RUN_TEST(test_create_light);
	RUN_TEST(test_create_plane);
	RUN_TEST(test_create_cylinder);
	RUN_TEST(test_create_sphere);
	return (0);
}
