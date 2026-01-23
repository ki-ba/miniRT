/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_sub_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:06:14 by abetemps          #+#    #+#             */
/*   Updated: 2026/01/11 13:47:51 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "vec3.h"

void	test_vec3_sub(void)
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	res;

	u = (t_vec3){0, 0, 0};
	v = (t_vec3){1, -2, 3};
	res = vec3_sub(u, v);
	TEST_ASSERT_EQUAL_DOUBLE(-1, res.x);
	TEST_ASSERT_EQUAL_DOUBLE(2, res.y);
	TEST_ASSERT_EQUAL_DOUBLE(-3, res.z);

	u = (t_vec3){1, 2, 3};
	v = (t_vec3){1, 2, 3};
	res = vec3_sub(u, v);
	TEST_ASSERT_EQUAL_DOUBLE(0, res.x);
	TEST_ASSERT_EQUAL_DOUBLE(0, res.y);
	TEST_ASSERT_EQUAL_DOUBLE(0, res.z);

	u = (t_vec3){4, 5, 6};
	v = (t_vec3){1, 2, 3};
	res = vec3_sub(u, v);
	TEST_ASSERT_EQUAL_DOUBLE(3, res.x);
	TEST_ASSERT_EQUAL_DOUBLE(3, res.y);
	TEST_ASSERT_EQUAL_DOUBLE(3, res.z);

	u = (t_vec3){-1.5, 2.0, -3.5};
	v = (t_vec3){1.5, -2.0, 3.5};
	res = vec3_sub(u, v);
	TEST_ASSERT_EQUAL_DOUBLE(-3.0, res.x);
	TEST_ASSERT_EQUAL_DOUBLE(4.0, res.y);
	TEST_ASSERT_EQUAL_DOUBLE(-7.0, res.z);

	u = (t_vec3){1e6, 1e6, 1e6};
	v = (t_vec3){-1e6, -1e6, -1e6};
	res = vec3_sub(u, v);
	TEST_ASSERT_EQUAL_DOUBLE(2e6, res.x);
	TEST_ASSERT_EQUAL_DOUBLE(2e6, res.y);
	TEST_ASSERT_EQUAL_DOUBLE(2e6, res.z);
}
