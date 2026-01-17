/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scale_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:17:09 by abetemps          #+#    #+#             */
/*   Updated: 2025/12/19 20:29:10 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "vec3.h"

void	test_vec3_scale(void)
{
	t_vec3	v;
	t_vec3 	res;
	double	s;

	v = (t_vec3) {0, 0, 0};
	s = 0.0;
	res = vec3_scale(v, s);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, res.x);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, res.y);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, res.z);

	s = 5.0;
	res = vec3_scale(v, s);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, res.x);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, res.y);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, res.z);

	v = (t_vec3) {1.0, -2.0, 3.0};
	s = 1.0;
	res = vec3_scale(v, s);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, res.x);
    TEST_ASSERT_EQUAL_DOUBLE(-2.0, res.y);
    TEST_ASSERT_EQUAL_DOUBLE(3.0, res.z);

	s = -2.0;
	res = vec3_scale(v, s);
    TEST_ASSERT_EQUAL_DOUBLE(-2.0, res.x);
    TEST_ASSERT_EQUAL_DOUBLE(4.0, res.y);
    TEST_ASSERT_EQUAL_DOUBLE(-6.0, res.z);

}

