/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:34:36 by abetemps          #+#    #+#             */
/*   Updated: 2025/12/19 20:29:03 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "vec3.h"

# define DELTA 1e-6
void	test_vec3_normalize(void)
{
    t_vec3	v;
	t_vec3	res;

	v = (t_vec3) {0.0, 0.0, 1.0};
    res = vec3_normalize(v);
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, res.x);
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, res.y);
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 1.0, res.z);

	v = (t_vec3) {3.0, 4.0, 12.0};
	res = vec3_normalize(v);
	double	len = vec3_magnitude(res);
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 1.0, len);

	v = (t_vec3) {2.0, -2.0, 4.0};
    res = vec3_normalize(v);
    /* res should be colinear with v: ratios equal */
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, res.x / res.z, v.x / v.z);
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, res.y / res.z, v.y / v.z);

	v = (t_vec3) {0.0, 0.0, 0.0};
    res = vec3_normalize(v);
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, res.x);
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, res.y);
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.0, res.z);

    v = (t_vec3) {-1.0, -1.0, -1.0};
    res = vec3_normalize(v);
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, -0.57735026, res.x);
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, -0.57735026, res.y);
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, -0.57735026, res.z);

    v = (t_vec3) {-0.90296227, 0.42971975, 0.0};
    res = vec3_normalize(v);
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, -0.90296227, res.x);
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.42971975, res.y);
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0, res.z);

    v = (t_vec3) {-100, 47.59, 0.0};
    res = vec3_normalize(v);
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, -0.90296227, res.x);
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0.42971975, res.y);
    TEST_ASSERT_DOUBLE_WITHIN(DELTA, 0, res.z);

}

