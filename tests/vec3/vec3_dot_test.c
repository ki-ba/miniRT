/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_dot_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:17:09 by abetemps          #+#    #+#             */
/*   Updated: 2025/12/19 20:28:49 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "vec3.h"

void	test_vec3_dot(void)
{
    t_vec3 u;
    t_vec3 v;
	double res;

    v = (t_vec3) {1.0, 2.0, 3.0};
    res = vec3_dot(&v, &v);
    TEST_ASSERT_EQUAL_DOUBLE(1.0*1.0 + 2.0*2.0 + 3.0*3.0, res);

    u = (t_vec3) {1.0, 0.0, 0.0};
    v = (t_vec3) {0.0, 1.0, 0.0};
    res = vec3_dot(&u, &v);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, res);

	u = (t_vec3) {1.0, 2.0, 3.0};
	v = (t_vec3) {2.0, 4.0, 6.0};
	res = vec3_dot(&u, &v);
	TEST_ASSERT_EQUAL_DOUBLE(1.0*2.0 + 2.0*4.0 + 3.0*6.0, res);

	u = (t_vec3) {1.0, 0.0, 0.0};
	v = (t_vec3) {-2.0, 0.0, 0.0};
	res = vec3_dot(&u, &v);
    TEST_ASSERT_EQUAL_DOUBLE(-2.0, res);

	u = (t_vec3) {1.0, 2.0, 3.0};
	v = (t_vec3) {0.0, 0.0, 0.0};
	res = vec3_dot(&u, &v);
	TEST_ASSERT_EQUAL_DOUBLE(0.0, res);
}

