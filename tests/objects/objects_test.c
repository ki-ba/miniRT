/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:23:41 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/04 14:26:11 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "unity.h"
#include "objects.h"

void test_create_plane(void)
{
	char	*plane_arr[] = { "pl", "0,0,0", "0,1,0", "255,0,0", NULL };
	t_plane	*plane;

	plane = create_plane(plane_arr);
	TEST_ASSERT_NOT_NULL(plane);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, plane->p.x);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, plane->p.y);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, plane->p.z);

	TEST_ASSERT_EQUAL_DOUBLE(0.0, plane->normal.x);
	TEST_ASSERT_EQUAL_DOUBLE(1.0, plane->normal.y);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, plane->normal.z);

	TEST_ASSERT_EQUAL_UINT8(255, plane->c.r);
	TEST_ASSERT_EQUAL_UINT8(0, plane->c.g);
	TEST_ASSERT_EQUAL_UINT8(0, plane->c.b);

	free(plane);
}

void test_create_cylinder(void)
{
	char	*cylinder_arr[] = { "cy", "0,0,0", "0,1,0", "5.0", "10.0", "0,255,0", NULL };
	t_cylinder	*cylinder;

	cylinder = create_cylinder(cylinder_arr);
	TEST_ASSERT_NOT_NULL(cylinder);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, cylinder->center.x);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, cylinder->center.y);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, cylinder->center.z);

	TEST_ASSERT_EQUAL_DOUBLE(0.0, cylinder->normal.x);
	TEST_ASSERT_EQUAL_DOUBLE(1.0, cylinder->normal.y);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, cylinder->normal.z);

	TEST_ASSERT_EQUAL_DOUBLE(5.0, cylinder->diameter);
	TEST_ASSERT_EQUAL_DOUBLE(10.0, cylinder->height);

	TEST_ASSERT_EQUAL_UINT8(0, cylinder->c.r);
	TEST_ASSERT_EQUAL_UINT8(255, cylinder->c.g);
	TEST_ASSERT_EQUAL_UINT8(0, cylinder->c.b);

	free(cylinder);
}

void test_create_sphere(void)
{
	char	*sphere_arr[] = { "sp", "0,0,0", "10.0", "0,0,255", NULL };
	t_sphere	*sphere;

	sphere = create_sphere(sphere_arr);
	TEST_ASSERT_NOT_NULL(sphere);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, sphere->center.x);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, sphere->center.y);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, sphere->center.z);

	TEST_ASSERT_EQUAL_DOUBLE(10.0, sphere->diameter);

	TEST_ASSERT_EQUAL_UINT8(0, sphere->c.r);
	TEST_ASSERT_EQUAL_UINT8(0, sphere->c.g);
	TEST_ASSERT_EQUAL_UINT8(255, sphere->c.b);

	free(sphere);
}

void	test_create_light(void)
{
	char	*light_arr[] = { "L", "10,20,30", "0.5", "255,255,255", NULL };
	t_light	*light;

	light = create_light(light_arr);
	TEST_ASSERT_NOT_NULL(light);
	TEST_ASSERT_EQUAL_DOUBLE(10.0, light->origin.x);
	TEST_ASSERT_EQUAL_DOUBLE(20.0, light->origin.y);
	TEST_ASSERT_EQUAL_DOUBLE(30.0, light->origin.z);

	TEST_ASSERT_EQUAL_DOUBLE(0.5, light->intensity);

	TEST_ASSERT_EQUAL_UINT8(255, light->color.r);
	TEST_ASSERT_EQUAL_UINT8(255, light->color.g);
	TEST_ASSERT_EQUAL_UINT8(255, light->color.b);

	free(light);
}
