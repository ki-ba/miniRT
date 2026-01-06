/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_add_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:06:14 by abetemps          #+#    #+#             */
/*   Updated: 2025/12/19 20:28:42 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "vec3.h"

void	test_vec3_add(void)
{
	t_vec3	u;
	t_vec3 	v;
	t_vec3 	res;

	u = (t_vec3){0, 0, 0};
	v = (t_vec3){1, -2, 3};
	res = vec3_add(&u, &v);
	TEST_ASSERT_EQUAL_DOUBLE(1, res.x);
	TEST_ASSERT_EQUAL_DOUBLE(-2, res.y);
	TEST_ASSERT_EQUAL_DOUBLE(3, res.z);

	u = (t_vec3){1, 2, 3};
	v = (t_vec3){4, 5, 6};
	res = vec3_add(&u, &v);
	TEST_ASSERT_EQUAL_DOUBLE(5, res.x);
	TEST_ASSERT_EQUAL_DOUBLE(7, res.y);
	TEST_ASSERT_EQUAL_DOUBLE(9, res.z);

	u = (t_vec3){-1, -2, -3};
	v = (t_vec3){1, 2, 3};
	res = vec3_add(&u, &v);
	TEST_ASSERT_EQUAL_DOUBLE(0, res.x);
	TEST_ASSERT_EQUAL_DOUBLE(0, res.y);
	TEST_ASSERT_EQUAL_DOUBLE(0, res.z);

	u = (t_vec3){1.5, -2.5, 3.5};
	v = (t_vec3){-1.5, 2.5, -3.5};
	res = vec3_add(&u, &v);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, res.x);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, res.y);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, res.z);

	u = (t_vec3){1e6, -1e6, 0};
	v = (t_vec3){-1e6, 1e6, 0};
	res = vec3_add(&u, &v);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, res.x);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, res.y);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, res.z);
}

