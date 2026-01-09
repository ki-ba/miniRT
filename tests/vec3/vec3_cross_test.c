/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_cross_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:30:25 by abetemps          #+#    #+#             */
/*   Updated: 2025/12/19 20:29:57 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "vec3.h"

void	test_vec3_cross(void)
{
	t_vec3	u;
	t_vec3 	v;
	t_vec3 	res;

	u = (t_vec3) {1.0, 0.0, 0.0};
    v = (t_vec3) {0.0, 1.0, 0.0};
    res = vec3_cross(u, v);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, res.x);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, res.y);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, res.z);

	u = (t_vec3) {1.0, 2.0, 3.0};
	v = (t_vec3) {4.0, 5.0, 6.0};
    t_vec3	uv = vec3_cross(u, v);
    t_vec3	vu = vec3_cross(v, u);
    TEST_ASSERT_EQUAL_DOUBLE(-uv.x, vu.x);
    TEST_ASSERT_EQUAL_DOUBLE(-uv.y, vu.y);
    TEST_ASSERT_EQUAL_DOUBLE(-uv.z, vu.z);

    v = (t_vec3) {2.0, 4.0, 6.0};
    res = vec3_cross(u, v);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, res.x);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, res.y);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, res.z);

	u = (t_vec3) {1.0, 0.0, 0.0};
    v = (t_vec3) {0.0, 1.0, 0.0};
    t_vec3	w = vec3_cross(u, v);
    double	dot_uw = vec3_dot(u, w);
    double	dot_vw = vec3_dot(v, w);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, dot_uw);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, dot_vw);

    t_vec3	zero = (t_vec3) {0.0, 0.0, 0.0};
	u = (t_vec3) {1.0, 2.0, 3.0};
    res = vec3_cross(u, zero);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, res.x);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, res.y);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, res.z);

}

