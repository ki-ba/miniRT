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
	t_object *plane;
	
	plane = ft_calloc(1, sizeof(t_object));

	create_plane(plane, plane_arr);
	TEST_ASSERT_NOT_NULL(plane);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, plane->p.x);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, plane->p.y);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, plane->p.z);

	TEST_ASSERT_EQUAL_DOUBLE(0.0, plane->n.x);
	TEST_ASSERT_EQUAL_DOUBLE(1.0, plane->n.y);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, plane->n.z);

	TEST_ASSERT_EQUAL_UINT8(255, plane->c.r);
	TEST_ASSERT_EQUAL_UINT8(0, plane->c.g);
	TEST_ASSERT_EQUAL_UINT8(0, plane->c.b);

	free(plane);
}

void test_create_cylinder(void)
{
	char		*cylinder_arr[] = { "cy", "0,0,0", "0,1,0", "5.0", "10.0", "0,255,0", NULL };
	t_object	*cylinder;

	cylinder = ft_calloc(1, sizeof(t_object));
	create_cylinder(cylinder, cylinder_arr);
	TEST_ASSERT_NOT_NULL(cylinder);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, cylinder->center.x);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, cylinder->center.y);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, cylinder->center.z);

	TEST_ASSERT_EQUAL_DOUBLE(0.0, cylinder->n.x);
	TEST_ASSERT_EQUAL_DOUBLE(1.0, cylinder->n.y);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, cylinder->n.z);

	TEST_ASSERT_EQUAL_DOUBLE(5.0, cylinder->diam);
	TEST_ASSERT_EQUAL_DOUBLE(10.0, cylinder->h);

	TEST_ASSERT_EQUAL_UINT8(0, cylinder->c.r);
	TEST_ASSERT_EQUAL_UINT8(255, cylinder->c.g);
	TEST_ASSERT_EQUAL_UINT8(0, cylinder->c.b);

	free(cylinder);
}

void test_create_sphere(void)
{
	char		*sphere_arr[] = { "sp", "0,0,0", "10.0", "0,0,255", NULL };
	t_object	*sphere;

	sphere = ft_calloc(1, sizeof(t_object));
	create_sphere(sphere, sphere_arr);
	TEST_ASSERT_NOT_NULL(sphere);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, sphere->center.x);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, sphere->center.y);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, sphere->center.z);

	TEST_ASSERT_EQUAL_DOUBLE(10.0, sphere->diam);

	TEST_ASSERT_EQUAL_UINT8(0, sphere->c.r);
	TEST_ASSERT_EQUAL_UINT8(0, sphere->c.g);
	TEST_ASSERT_EQUAL_UINT8(255, sphere->c.b);

	free(sphere);
}

void	test_create_light(void)
{
	char		*light_arr[] = { "L", "10,20,30", "0.5", "255,255,255", NULL };
	t_light		*light;

	light = ft_calloc(1, sizeof(t_object));

	create_light(light, light_arr);
	TEST_ASSERT_NOT_NULL(light);
	TEST_ASSERT_EQUAL_DOUBLE(10.0, light->ori.x);
	TEST_ASSERT_EQUAL_DOUBLE(20.0, light->ori.y);
	TEST_ASSERT_EQUAL_DOUBLE(30.0, light->ori.z);

	TEST_ASSERT_EQUAL_DOUBLE(0.5, light->i);

	TEST_ASSERT_EQUAL_UINT8(255, light->c.r);
	TEST_ASSERT_EQUAL_UINT8(255, light->c.g);
	TEST_ASSERT_EQUAL_UINT8(255, light->c.b);

	free(light);
}
