/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_properties_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:53:01 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/08 14:39:50 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "parsing.h"

void	test_read_color(void)
{
	t_color color;
	int		status;

	status = read_color(&color, "255,0,128");
	TEST_ASSERT_EQUAL_INT(0, status);
	TEST_ASSERT_EQUAL_UINT8(255, color.r);
	TEST_ASSERT_EQUAL_UINT8(0, color.g);
	TEST_ASSERT_EQUAL_UINT8(128, color.b);
	status = read_color(&color, "0,255,64");
	TEST_ASSERT_EQUAL_INT(0, status);
	TEST_ASSERT_EQUAL_UINT8(0, color.r);
	TEST_ASSERT_EQUAL_UINT8(255, color.g);
	TEST_ASSERT_EQUAL_UINT8(64, color.b);
	status = read_color(&color, "3d4,67,89");
	TEST_ASSERT_NOT_EQUAL(0, status);
	status = read_color(&color, "256,0,0");
	TEST_ASSERT_NOT_EQUAL(0, status);
	status = read_color(&color, "-1,0,0");
	TEST_ASSERT_NOT_EQUAL(0, status);
	status = read_color(&color, "100,100");
	TEST_ASSERT_NOT_EQUAL(0, status);
	status = read_color(NULL, "100,100,100");
	TEST_ASSERT_NOT_EQUAL(0, status);
	status = read_color(&color, "100,100,100,50");
	TEST_ASSERT_NOT_EQUAL_INT(0, status);
	status = read_color(&color, "100,,100");
	TEST_ASSERT_NOT_EQUAL(0, status);
}

void	test_read_point(void)
{
	t_point	point;
	int		status;

	status = read_point(&point, "1.0,2.0,3.0");
	TEST_ASSERT_EQUAL_INT(0, status);
	TEST_ASSERT_EQUAL_DOUBLE(1.0, point.x);
	TEST_ASSERT_EQUAL_DOUBLE(2.0, point.y);
	TEST_ASSERT_EQUAL_DOUBLE(3.0, point.z);
	status = read_point(&point, "-1.5,0.0,1.5");
	TEST_ASSERT_EQUAL_INT(0, status);
	TEST_ASSERT_EQUAL_DOUBLE(-1.5, point.x);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, point.y);
	TEST_ASSERT_EQUAL_DOUBLE(1.5, point.z);
	status = read_point(NULL, "1.0,2.0,3.0");
	TEST_ASSERT_NOT_EQUAL(0, status);
	status = read_point(&point, "1.0,2.0");
	TEST_ASSERT_NOT_EQUAL(0, status);
	status = read_point(&point, "a,b,c");
	TEST_ASSERT_NOT_EQUAL(0, status);
	status = read_point(&point, "1.0,,3.0");
	TEST_ASSERT_NOT_EQUAL(0, status);
	status = read_point(&point, "1.0,2.0,");
	TEST_ASSERT_NOT_EQUAL(0, status);
	status = read_point(&point, "1.0,2.0,3.0,4.0");
	TEST_ASSERT_NOT_EQUAL(0, status);
}

void	test_read_normalized_vec(void)
{
	t_vec3	vec;
	int		status;

	status = read_normalized_vec(&vec, "0.0,1.0,0.0");
	TEST_ASSERT_EQUAL_INT(0, status);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, vec.x);
	TEST_ASSERT_EQUAL_DOUBLE(1.0, vec.y);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, vec.z);

	status = read_normalized_vec(&vec, "-0.57735,.57735,0.57735");
	TEST_ASSERT_EQUAL_INT(0, status);
	TEST_ASSERT_EQUAL_DOUBLE(-0.57735, vec.x);
	TEST_ASSERT_EQUAL_DOUBLE(0.57735, vec.y);
	TEST_ASSERT_EQUAL_DOUBLE(0.57735, vec.z);

	status = read_normalized_vec(NULL, "0.0,1.0,0.0");
	TEST_ASSERT_NOT_EQUAL(0, status);

	status = read_normalized_vec(&vec, "1.0,0.0");
	TEST_ASSERT_NOT_EQUAL(0, status);

	status = read_normalized_vec(&vec, "1,,2,3");
	TEST_ASSERT_NOT_EQUAL(0, status);

	status = read_normalized_vec(&vec, "1,00");
	TEST_ASSERT_NOT_EQUAL(0, status);
}
